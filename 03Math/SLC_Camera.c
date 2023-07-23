#include "SLC/SLC_Camera.h"
#include "SLC/SLC_NumbersCopy.h"
#include <errno.h>
#pragma region Camera-matrix-with-basetype-r32
SLC_CTMatr32_t SLC_Camerar32_Direction(
    SLC_CPntr32_t cameraIsAt, SLC_CPntr32_t cameraLookAt, SLC_Vecr32_t work)
{
    SLC_r32_t dir_rot_right[16] = IMat_r32, dir_rot_left[16] = IMat_r32; // first and second rotation matrix from negative z-axis to actual view-direction
    SLC_r32_t dir_90degs[16] = IMat_r32, local_work[16];
    SLC_4r32_t viewlineVector;
    SLC_Polarr32_t polar;
    // rotate 90 degs around x-axis (Y-axis to Z-axis)
    // This convers from default camera viewline axis to Polar-Y coordinate reference axis.
    dir_90degs[10] = (dir_90degs[5] = SLC_r32_units[0]);
    dir_90degs[6] = -(dir_90degs[9] = SLC_r32_units[1]);
    SLC_Vecr32_Vector(viewlineVector, cameraIsAt, cameraLookAt);

    // convert viewline vector to polar representation
    SLC_PolarYFromCartesianr32(&polar, viewlineVector);

    // rotate theta around x-axis (Y-axis to Z-axis)
    dir_rot_right[5] = dir_rot_right[10] = polar.ctheta;
    dir_rot_right[6] = -(dir_rot_right[9] = polar.stheta);

    // rotate phi around y-axis (Z-axis to X-axis)
    dir_rot_left[0] = dir_rot_left[10] = polar.cphi;
    dir_rot_left[8] = -(dir_rot_left[2] = polar.sphi);
    return SLC_TMatr32_Mul(dir_rot_left, 
        SLC_TMatr32_Mul(dir_rot_right, dir_90degs, local_work), work);
}

SLC_CTMatr32_t SLC_Camerar32_Position(SLC_PCCameraPositionr32_t pos, SLC_TMatr32_t work)
{
    int err = EXIT_SUCCESS;
    SLC_r32_t dir_rot_[16];
    SLC_CTMatr32_t dir_rot;
    SLC_r32_t viewline_rotation[16] = IMat_r32; // rotation matrix around view-line
    SLC_r32_t moving_origin[16] = IMat_r32; // parallel moving matrix from origin to camera positioin
    do {
        // 1) Set rotation around view axis
        viewline_rotation[0] = viewline_rotation[5] = pos->viewAxisRotationCosSin[0];
        viewline_rotation[1] = -(viewline_rotation[4] = pos->viewAxisRotationCosSin[1]);

        // 2) Set viewline angle
        dir_rot = SLC_Camerar32_Direction(pos->cameraIsAt, pos->lookAt, dir_rot_);

        // 3) Set parallel movement
        moving_origin[3] = pos->cameraIsAt[0] / pos->cameraIsAt[3];
        moving_origin[7] = pos->cameraIsAt[1] / pos->cameraIsAt[3];
        moving_origin[11] = pos->cameraIsAt[2] / pos->cameraIsAt[3];

        // 4) multiply moving_origin, camera direction, and viewline_rotation
        SLC_CTMatr32_t prod_all = NULL;
        {
            SLC_16r32_t prod1, prod2;
            prod_all = SLC_TMatr32_Mul(
                moving_origin, SLC_TMatr32_Mul(
                    dir_rot, viewline_rotation, prod1
                ), prod2
            );
        }

        // 5) invert the product of the four matrices
        if  (!SLC_TMatr32_Inv(prod_all, work))
        {
            err = SLC_ESINGULAR;
            break;
        }
    } while (0);
    if (err)
    {
        work = NULL;
    }
    return work;
}

SLC_CTMatr32_t SLC_Camerar32_Orth(
    SLC_PCProjectionr32_t projconf,
    SLC_TMatr32_t work
) {
    int err = EXIT_SUCCESS;
    const SLC_r32_t _2 = SLC_r32_units[1] + SLC_r32_units[1];
    SLC_r32_copy(work, 1, SLC_r32_units, 0, 16); // zero clear work
    do {
        SLC_r32_t znear = projconf->far_near[1], zfar = projconf->far_near[0];
        SLC_r32_t zspan = znear - zfar;
        SLC_r32_t max_wh = SLC_r32_max(projconf->width_height[0], projconf->width_height[1]);
        if ((zspan < SLC_r32_units[0]) || (znear > SLC_r32_units[0]))
        { // zspan is negative or view depth range is reversed.
            err = EINVAL;
            break;
        }
        if (zspan < (max_wh * SLC_r32_stdtol))
        { // zspan is too small
            err = SLC_ESINGULAR;
            break;
        }
        work[0] = _2 / projconf->width_height[0];
        work[5] = _2 / projconf->width_height[1];
        work[10] = _2 / (projconf->far_near[1] - projconf->far_near[0]);
        work[11] = -(projconf->far_near[0] + projconf->far_near[1]) / 
            (projconf->far_near[1] - projconf->far_near[0]);
        work[15] = SLC_r32_units[1];
    } while (0);
    if (err)
    {
        errno = err;
        work = NULL;
    }
    return work;
}

SLC_CTMatr32_t SLC_Camerar32_Perspective(
    SLC_PCProjectionr32_t projconf,
    SLC_TMatr32_t work
) {
    int err = EXIT_SUCCESS;
    const SLC_r32_t _1 = SLC_r32_units[1];
    const SLC_r32_t _2 = _1 + _1;
    SLC_r32_copy(work, 1, SLC_r32_units, 0, 16); // zero clear work
    do {
        SLC_r32_t znear = projconf->far_near[1], zfar = projconf->far_near[0];
        SLC_r32_t zspan = znear - zfar;
        SLC_r32_t max_wh = SLC_r32_max(projconf->width_height[0], projconf->width_height[1]);
        if ((zspan < SLC_r32_units[0]) || (znear > SLC_r32_units[0]))
        { // zspan is negative or view depth range is reversed.
            err = EINVAL;
            break;
        }
        if (zspan < (max_wh * SLC_r32_stdtol))
        { // zspan is too small
            err = SLC_ESINGULAR;
            break;
        }
        work[0] = _2 * znear / projconf->width_height[0];
        work[5] = _2 * znear / projconf->width_height[1];
        work[10] = (projconf->far_near[0] + projconf->far_near[1])/zspan;
        work[11] = -_2 * projconf->far_near[0] * projconf->far_near[1]/zspan;
        work[14] = _1;
    } while (0);
    if (err)
    {
        errno = err;
        work = NULL;
    }
    return work;
}

#define _1 ((SLC_r32_t)1)
#define _m1 ((SLC_r32_t)(-1))
#define _0 ((SLC_r32_t)0)
static SLC_CTMatr32_t SLC_Camerar32_ReverseZ()
{    
    static const SLC_r32_t mat[] =
    {
        _1, _0, _0, _0,
        _0, _1, _0, _0,
        _0, _0, _m1, _0,
        _0, _0, _0, _1
    };
    return mat;
}
#undef _1
#undef _m1
#undef _0

SLC_CTMatr32_t SLC_Camerar32_OrthRZ(
    SLC_PCProjectionr32_t projconf,
    SLC_TMatr32_t work
) {
    SLC_r32_t local_work[16];
    SLC_CTMatr32_t orth = SLC_Camerar32_Orth(projconf, local_work);
    if (!orth)
    {
        return NULL;
    }
    return SLC_TMatr32_Mul(SLC_Camerar32_ReverseZ(), orth, work);
}

SLC_CTMatr32_t SLC_Camerar32_PerspectiveRZ(
    SLC_PCProjectionr32_t projconf,
    SLC_TMatr32_t work
) {
    SLC_r32_t local_work[16];
    SLC_CTMatr32_t pers = SLC_Camerar32_Perspective(projconf, local_work);
    if (!pers)
    {
        return NULL;
    }
    return SLC_TMatr32_Mul(SLC_Camerar32_ReverseZ(), pers, work);
}
#pragma endregion Camera-matrix-with-basetype-r32
#pragma region Camera-matrix-with-basetype-r64
SLC_CTMatr64_t SLC_Camerar64_Direction(
    SLC_CPntr64_t cameraIsAt, SLC_CPntr64_t cameraLookAt, SLC_Vecr64_t work)
{
    SLC_r64_t dir_rot_right[16] = IMat_r32, dir_rot_left[16] = IMat_r32; // first and second rotation matrix from negative z-axis to actual view-direction
    SLC_r64_t dir_90degs[16] = IMat_r32, local_work[16];
    SLC_4r64_t viewlineVector;
    SLC_Polarr64_t polar;
    // rotate 90 degs around x-axis (Y-axis to Z-axis)
    // This convers from default camera viewline axis to Polar-Y coordinate reference axis.
    dir_90degs[10] = (dir_90degs[5] = SLC_r64_units[0]);
    dir_90degs[6] = -(dir_90degs[9] = SLC_r64_units[1]);
    SLC_Vecr64_Vector(viewlineVector, cameraIsAt, cameraLookAt);

    // convert viewline vector to polar representation
    SLC_PolarYFromCartesianr64(&polar, viewlineVector);

    // rotate theta around x-axis (Y-axis to Z-axis)
    dir_rot_right[5] = dir_rot_right[10] = polar.ctheta;
    dir_rot_right[6] = -(dir_rot_right[9] = polar.stheta);

    // rotate phi around y-axis (Z-axis to X-axis)
    dir_rot_left[0] = dir_rot_left[10] = polar.cphi;
    dir_rot_left[8] = -(dir_rot_left[2] = polar.sphi);
    return SLC_TMatr64_Mul(dir_rot_left, 
        SLC_TMatr64_Mul(dir_rot_right, dir_90degs, local_work), work);
}

SLC_CTMatr64_t SLC_Camerar64_Position(SLC_PCCameraPositionr64_t pos, SLC_TMatr64_t work)
{
    int err = EXIT_SUCCESS;
    SLC_r64_t dir_rot_[16];
    SLC_CTMatr64_t dir_rot;
    SLC_r64_t viewline_rotation[16] = IMat_r32; // rotation matrix around view-line
    SLC_r64_t moving_origin[16] = IMat_r32; // parallel moving matrix from origin to camera positioin
    do {
        // 1) Set rotation around view axis
        viewline_rotation[0] = viewline_rotation[5] = pos->viewAxisRotationCosSin[0];
        viewline_rotation[1] = -(viewline_rotation[4] = pos->viewAxisRotationCosSin[1]);

        // 2) Set viewline angle
        dir_rot = SLC_Camerar64_Direction(pos->cameraIsAt, pos->lookAt, dir_rot_);

        // 3) Set parallel movement
        moving_origin[3] = pos->cameraIsAt[0] / pos->cameraIsAt[3];
        moving_origin[7] = pos->cameraIsAt[1] / pos->cameraIsAt[3];
        moving_origin[11] = pos->cameraIsAt[2] / pos->cameraIsAt[3];

        // 4) multiply moving_origin, camera direction, and viewline_rotation
        SLC_CTMatr64_t prod_all = NULL;
        {
            SLC_16r64_t prod1, prod2;
            prod_all = SLC_TMatr64_Mul(
                moving_origin, SLC_TMatr64_Mul(
                    dir_rot, viewline_rotation, prod1
                ), prod2
            );
        }

        // 5) invert the product of the four matrices
        if  (!SLC_TMatr64_Inv(prod_all, work))
        {
            err = SLC_ESINGULAR;
            break;
        }
    } while (0);
    if (err)
    {
        work = NULL;
    }
    return work;
}

SLC_CTMatr64_t SLC_Camerar64_Orth(
    SLC_PCProjectionr64_t projconf,
    SLC_TMatr64_t work
) {
    int err = EXIT_SUCCESS;
    const SLC_r64_t _2 = SLC_r64_units[1] + SLC_r64_units[1];
    SLC_r64_copy(work, 1, SLC_r64_units, 0, 16); // zero clear work
    do {
        SLC_r64_t znear = projconf->far_near[1], zfar = projconf->far_near[0];
        SLC_r64_t zspan = znear - zfar;
        SLC_r64_t max_wh = SLC_r64_max(projconf->width_height[0], projconf->width_height[1]);
        if ((zspan < SLC_r64_units[0]) || (znear > SLC_r64_units[0]))
        { // zspan is negative or view depth range is reversed.
            err = EINVAL;
            break;
        }
        if (zspan < (max_wh * SLC_r64_stdtol))
        { // zspan is too small
            err = SLC_ESINGULAR;
            break;
        }
        work[0] = _2 / projconf->width_height[0];
        work[5] = _2 / projconf->width_height[1];
        work[10] = _2 / (projconf->far_near[1] - projconf->far_near[0]);
        work[11] = -(projconf->far_near[0] + projconf->far_near[1]) / 
            (projconf->far_near[1] - projconf->far_near[0]);
        work[15] = SLC_r64_units[1];
    } while (0);
    if (err)
    {
        errno = err;
        work = NULL;
    }
    return work;
}

SLC_CTMatr64_t SLC_Camerar64_Perspective(
    SLC_PCProjectionr64_t projconf,
    SLC_TMatr64_t work
) {
    int err = EXIT_SUCCESS;
    const SLC_r64_t _1 = SLC_r64_units[1];
    const SLC_r64_t _2 = _1 + _1;
    SLC_r64_copy(work, 1, SLC_r64_units, 0, 16); // zero clear work
    do {
        SLC_r64_t znear = projconf->far_near[1], zfar = projconf->far_near[0];
        SLC_r64_t zspan = znear - zfar;
        SLC_r64_t max_wh = SLC_r64_max(projconf->width_height[0], projconf->width_height[1]);
        if ((zspan < SLC_r64_units[0]) || (znear > SLC_r64_units[0]))
        { // zspan is negative or view depth range is reversed.
            err = EINVAL;
            break;
        }
        if (zspan < (max_wh * SLC_r64_stdtol))
        { // zspan is too small
            err = SLC_ESINGULAR;
            break;
        }
        work[0] = _2 * znear / projconf->width_height[0];
        work[5] = _2 * znear / projconf->width_height[1];
        work[10] = (projconf->far_near[0] + projconf->far_near[1])/zspan;
        work[11] = -_2 * projconf->far_near[0] * projconf->far_near[1]/zspan;
        work[14] = _1;
    } while (0);
    if (err)
    {
        errno = err;
        work = NULL;
    }
    return work;
}

#define _1 ((SLC_r64_t)1)
#define _m1 ((SLC_r64_t)(-1))
#define _0 ((SLC_r64_t)0)
static SLC_CTMatr64_t SLC_Camerar64_ReverseZ()
{    
    static const SLC_r64_t mat[] =
    {
        _1, _0, _0, _0,
        _0, _1, _0, _0,
        _0, _0, _m1, _0,
        _0, _0, _0, _1
    };
    return mat;
}
#undef _1
#undef _m1
#undef _0

SLC_CTMatr64_t SLC_Camerar64_OrthRZ(
    SLC_PCProjectionr64_t projconf,
    SLC_TMatr64_t work
) {
    SLC_r64_t local_work[16];
    SLC_CTMatr64_t orth = SLC_Camerar64_Orth(projconf, local_work);
    if (!orth)
    {
        return NULL;
    }
    return SLC_TMatr64_Mul(SLC_Camerar64_ReverseZ(), orth, work);
}

SLC_CTMatr64_t SLC_Camerar64_PerspectiveRZ(
    SLC_PCProjectionr64_t projconf,
    SLC_TMatr64_t work
) {
    SLC_r64_t local_work[16];
    SLC_CTMatr64_t pers = SLC_Camerar64_Perspective(projconf, local_work);
    if (!pers)
    {
        return NULL;
    }
    return SLC_TMatr64_Mul(SLC_Camerar64_ReverseZ(), pers, work);
}
#pragma endregion Camera-matrix-with-basetype-r64
