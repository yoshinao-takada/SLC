#include "SLC/SLC_Camera.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <assert.h>

#pragma region Polar-Y__Cartesian__Conversion_r32
typedef struct {
    SLC_4r32_t Nx, Ny, Nz;
    SLC_Polarr32_t NxPolarY, NyPolarY, NzPolarY;
} CameraUTPolarYDatar32_t, *pCameraUTPolarYDatar32_t;
typedef const CameraUTPolarYDatar32_t *pcCameraUTPolarYDatar32_t;

bool AreEqualPolarYr32(SLC_PCPolarr32_t ref, SLC_PCPolarr32_t tested, SLC_r32_t tol)
{
    bool b = SLC_r32_areequal(ref->r, tested->r, tol);
    b &= SLC_r32_areequal(ref->cphi, tested->cphi, tol);
    b &= SLC_r32_areequal(ref->sphi, tested->sphi, tol);
    b &= SLC_r32_areequal(ref->ctheta, tested->ctheta, tol);
    b &= SLC_r32_areequal(ref->stheta, tested->stheta, tol);
    return b;
}

bool AreEqual4r32(SLC_CPntr32_t ref, SLC_CPntr32_t tested, SLC_r32_t tol)
{
    bool b = SLC_r32_areequal(ref[0]/ref[3], tested[0]/tested[3], tol);
    b &= SLC_r32_areequal(ref[1]/ref[3], tested[1]/tested[3], tol);
    b &= SLC_r32_areequal(ref[2]/ref[3], tested[2]/tested[3], tol);
    return b;
}

SLC_errno_t SLC_r32_PolarYUT(SLC_PCTestArgs_t args)
{
    const CameraUTPolarYDatar32_t* data = (const CameraUTPolarYDatar32_t*)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_Polarr32_t polar;
    SLC_4r32_t restored;
    do {
        SLC_PolarYFromCartesianr32(&polar, data->Nx);
        if (!AreEqualPolarYr32(&data->NxPolarY, &polar, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_PolarYToCartesianr32(restored, &polar);
        if (!AreEqual4r32(data->Nx, restored, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }

        SLC_PolarYFromCartesianr32(&polar, data->Ny);
        if (!AreEqualPolarYr32(&data->NyPolarY, &polar, ((SLC_r32_t)1000) * SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_PolarYToCartesianr32(restored, &polar);
        if (!AreEqual4r32(data->Ny, restored, ((SLC_r32_t)1000) * SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }

        SLC_PolarYFromCartesianr32(&polar, data->Nz);
        if (!AreEqualPolarYr32(&data->NzPolarY, &polar, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_PolarYToCartesianr32(restored, &polar);
        if (!AreEqual4r32(data->Nz, restored, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_CameraDirectionUT(SLC_PCTestArgs_t args)
{
    const SLC_r32_t _0 = SLC_r32_units[0], _1 = SLC_r32_units[1], _minus1 = SLC_r32_units[2];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCCameraPositionr32_t arg = args->data;
    SLC_r32_t m_rot_[16], v_lookAt_[4], v_lookAt_ref[4];
    SLC_4r32_t negZ = { _0, _0, _minus1, _1 };
    for (int i = 0; i < 4; i++, arg++)
    {
        SLC_CTMatr32_t m_rot = SLC_Camerar32_Direction(
            arg-> cameraIsAt, arg->lookAt, m_rot_);
        SLC_CVecr32_t v_lookAt = SLC_TMatr32_Transform(m_rot, negZ, v_lookAt_);
        SLC_Vecr32_Vector(v_lookAt_ref, arg-> cameraIsAt, arg->lookAt);
        SLC_r32_t len_v_lookAt = SLC_r32sqrt(SLC_Vecr32_InnerProduct(v_lookAt, v_lookAt));
        SLC_r32_t len_v_lookAt_ref = SLC_r32sqrt(SLC_Vecr32_InnerProduct(v_lookAt_ref, v_lookAt_ref));
        SLC_r32_t v_lookAt_dot_v_lookAt_ref = SLC_Vecr32_InnerProduct(v_lookAt, v_lookAt_ref);
        //printf("--- m_rot =\n");
        //SLC_TMatr32_Print(stdout, m_rot);
        //printf("--- v_lookAt = ");
        //SLC_Vecr32_Print(stdout, v_lookAt);
        //printf("--- v_lookAt_ref = ");
        //SLC_Vecr32_Print(stdout, v_lookAt_ref);
        if (!SLC_r32_areequal(len_v_lookAt, _1, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(v_lookAt_dot_v_lookAt_ref, len_v_lookAt_ref, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_CameraPositionUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCCameraPositionr32_t arg = args->data;
    SLC_r32_t mpos_[16], cameraIsAt_transformed_[4], lookAt_transformed_[4];
    SLC_r32_t _0 = SLC_r32_units[0], _1 = SLC_r32_units[1];
    for (int i = 0; i < 4; i++, args++)
    {
        const SLC_r32_t origin[4] = { _0, _0, _0, _1 };
        SLC_r32_t camera_lookAt_vector[4];
        SLC_Vecr32_Vector(camera_lookAt_vector, arg->cameraIsAt, arg->lookAt);
        const SLC_r32_t lookAt_ref[4] = {
             _0, _0, 
             -SLC_r32sqrt(SLC_Vecr32_InnerProduct(camera_lookAt_vector, camera_lookAt_vector)), 
             _1 };
        SLC_CTMatr32_t mpos = SLC_Camerar32_Position(arg, mpos_);
        SLC_CPntr32_t cameraIsAt_transformed = SLC_TMatr32_Transform(mpos, arg->cameraIsAt, cameraIsAt_transformed_);
        SLC_CPntr32_t lookAt_transformed = SLC_TMatr32_Transform(mpos, arg->lookAt, lookAt_transformed_);
        if (!SLC_Pntr32_areequal(origin, cameraIsAt_transformed, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Pntr32_areequal(lookAt_ref, lookAt_transformed, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_CameraOrthUT(SLC_PCTestArgs_t args)
{
    const SLC_r32_t _0 = SLC_r32_units[0], _1 = SLC_r32_units[1], _minus1 = SLC_r32_units[2];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCProjectionr32_t proj = args->data;
    const SLC_4r32_t 
        projected_left_bottom_far_ref = { _minus1, _minus1, _minus1, _1 },
        projected_right_top_near_ref = { _1, _1, _1, _1 };
    for (int i = 0; i < 2; i++, proj++)
    {
        SLC_r32_t workPnt[4], workMat[16];
        SLC_CTMatr32_t projMat = SLC_Camerar32_Orth(proj, workMat);
        SLC_r32_t xLeft = -proj->width_height[0]/(2 * _1);
        SLC_r32_t yBottom = -proj->width_height[1]/(2 * _1);
        SLC_r32_t zFar = proj->far_near[0];
        SLC_r32_t zNear = proj->far_near[1];
        const SLC_4r32_t
            left_bottom_far = { xLeft, yBottom, zFar, _1 },
            right_top_near = { -xLeft, -yBottom, zNear, _1 };
        fprintf(stderr, "--- projMat =\n");
        SLC_TMatr32_Print(stderr, projMat);
        SLC_CPntr32_t projected = SLC_TMatr32_Transform(projMat, left_bottom_far, workPnt);
        fprintf(stderr, "--- projected left_bottom_far = ");
        SLC_Pntr32_Print(stderr, projected);
        if (!SLC_Pntr32_areequal(
            projected_left_bottom_far_ref, projected, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        projected = SLC_TMatr32_Transform(projMat, right_top_near, workPnt);
        fprintf(stderr, "--- projected right_top_near = ");
        SLC_Pntr32_Print(stderr, projected);
        if (!SLC_Pntr32_areequal(
            projected_right_top_near_ref, projected, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}


SLC_errno_t SLC_r32_CameraPersUT(SLC_PCTestArgs_t args)
{
    const SLC_r32_t _0 = SLC_r32_units[0], _1 = SLC_r32_units[1], _minus1 = SLC_r32_units[2];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCProjectionr32_t proj = args->data;
    SLC_r32_t workmat[16], workpnt[4];
    for (int i = 0; i < 2; i++, proj++)
    {
        SLC_r32_t xLeft = -proj->width_height[0]/((SLC_r32_t)2);
        SLC_r32_t yBottom = -proj->width_height[1]/((SLC_r32_t)2);
        SLC_r32_t zFar = proj->far_near[0], zNear = proj->far_near[1];
        SLC_r32_t zRatio = zFar/zNear;
        const SLC_4r32_t
            left_bottom_far = { zRatio * xLeft, zRatio * yBottom, zFar, _1 },
            right_top_near = { -xLeft, -yBottom, zNear, _1 },
            center_far = { _0, _0, zFar, _1 },
            center_near = { _0, _0, zNear, _1 };
        SLC_CTMatr32_t projmat = SLC_Camerar32_Perspective(proj, workmat);
        //printf("--- projmat = \n"); SLC_TMatr32_Print(stdout, projmat);
        {
            const SLC_4r32_t transformed_ref = { -_1, -_1, -_1, _1 };
            SLC_CPntr32_t transformed = SLC_TMatr32_Transform(projmat, left_bottom_far, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr32_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr32_Print(stdout, transformed);
            if (!SLC_Pntr32_areequal(transformed_ref, transformed, SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
        {
            const SLC_4r32_t transformed_ref = { _1, _1, _1, _1 };
            SLC_CPntr32_t transformed = SLC_TMatr32_Transform(projmat, right_top_near, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr32_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr32_Print(stdout, transformed);
            if (!SLC_Pntr32_areequal(transformed_ref, transformed, SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
        {
            const SLC_4r32_t transformed_ref = { _0, _0, -_1, _1 };
            SLC_CPntr32_t transformed = SLC_TMatr32_Transform(projmat, center_far, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr32_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr32_Print(stdout, transformed);
            if (!SLC_Pntr32_areequal(transformed_ref, transformed, SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
        {
            const SLC_4r32_t transformed_ref = { _0, _0, _1, _1 };
            SLC_CPntr32_t transformed = SLC_TMatr32_Transform(projmat, center_near, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr32_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr32_Print(stdout, transformed);
            if (!SLC_Pntr32_areequal(transformed_ref, transformed, SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Polar-Y__Cartesian__Conversion_r32
#pragma region Polar-Y__Cartesian__Conversion_r64
typedef struct {
    SLC_4r64_t Nx, Ny, Nz;
    SLC_Polarr64_t NxPolarY, NyPolarY, NzPolarY;
} CameraUTPolarYDatar64_t, *pCameraUTPolarYDatar64_t;
typedef const CameraUTPolarYDatar64_t *pcCameraUTPolarYDatar64_t;

bool AreEqualPolarYr64(SLC_PCPolarr64_t ref, SLC_PCPolarr64_t tested, SLC_r64_t tol)
{
    bool b = SLC_r64_areequal(ref->r, tested->r, tol);
    b &= SLC_r64_areequal(ref->cphi, tested->cphi, tol);
    b &= SLC_r64_areequal(ref->sphi, tested->sphi, tol);
    b &= SLC_r64_areequal(ref->ctheta, tested->ctheta, tol);
    b &= SLC_r64_areequal(ref->stheta, tested->stheta, tol);
    return b;
}

bool AreEqual4r64(SLC_CPntr64_t ref, SLC_CPntr64_t tested, SLC_r64_t tol)
{
    bool b = SLC_r64_areequal(ref[0]/ref[3], tested[0]/tested[3], tol);
    b &= SLC_r64_areequal(ref[1]/ref[3], tested[1]/tested[3], tol);
    b &= SLC_r64_areequal(ref[2]/ref[3], tested[2]/tested[3], tol);
    return b;
}

SLC_errno_t SLC_r64_PolarYUT(SLC_PCTestArgs_t args)
{
    const CameraUTPolarYDatar64_t* data = (const CameraUTPolarYDatar64_t*)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_Polarr64_t polar;
    SLC_4r64_t restored;
    do {
        SLC_PolarYFromCartesianr64(&polar, data->Nx);
        if (!AreEqualPolarYr64(&data->NxPolarY, &polar, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_PolarYToCartesianr64(restored, &polar);
        if (!AreEqual4r64(data->Nx, restored, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }

        SLC_PolarYFromCartesianr64(&polar, data->Ny);
        if (!AreEqualPolarYr64(&data->NyPolarY, &polar, ((SLC_r64_t)1000) * SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_PolarYToCartesianr64(restored, &polar);
        if (!AreEqual4r64(data->Ny, restored, ((SLC_r64_t)1000) * SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }

        SLC_PolarYFromCartesianr64(&polar, data->Nz);
        if (!AreEqualPolarYr64(&data->NzPolarY, &polar, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_PolarYToCartesianr64(restored, &polar);
        if (!AreEqual4r64(data->Nz, restored, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_CameraDirectionUT(SLC_PCTestArgs_t args)
{
    const SLC_r64_t _0 = SLC_r64_units[0], _1 = SLC_r64_units[1], _minus1 = SLC_r64_units[2];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCCameraPositionr64_t arg = args->data;
    SLC_r64_t m_rot_[16], v_lookAt_[4], v_lookAt_ref[4];
    SLC_4r64_t negZ = { _0, _0, _minus1, _1 };
    for (int i = 0; i < 4; i++, arg++)
    {
        SLC_CTMatr64_t m_rot = SLC_Camerar64_Direction(
            arg-> cameraIsAt, arg->lookAt, m_rot_);
        SLC_CVecr64_t v_lookAt = SLC_TMatr64_Transform(m_rot, negZ, v_lookAt_);
        SLC_Vecr64_Vector(v_lookAt_ref, arg-> cameraIsAt, arg->lookAt);
        SLC_r64_t len_v_lookAt = SLC_r64sqrt(SLC_Vecr64_InnerProduct(v_lookAt, v_lookAt));
        SLC_r64_t len_v_lookAt_ref = SLC_r64sqrt(SLC_Vecr64_InnerProduct(v_lookAt_ref, v_lookAt_ref));
        SLC_r64_t v_lookAt_dot_v_lookAt_ref = SLC_Vecr64_InnerProduct(v_lookAt, v_lookAt_ref);
        //printf("--- m_rot =\n");
        //SLC_TMatr64_Print(stdout, m_rot);
        //printf("--- v_lookAt = ");
        //SLC_Vecr64_Print(stdout, v_lookAt);
        //printf("--- v_lookAt_ref = ");
        //SLC_Vecr64_Print(stdout, v_lookAt_ref);
        if (!SLC_r64_areequal(len_v_lookAt, _1, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(v_lookAt_dot_v_lookAt_ref, len_v_lookAt_ref, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_CameraPositionUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCCameraPositionr64_t arg = args->data;
    SLC_r64_t mpos_[16], cameraIsAt_transformed_[4], lookAt_transformed_[4];
    SLC_r64_t _0 = SLC_r64_units[0], _1 = SLC_r64_units[1];
    for (int i = 0; i < 4; i++, args++)
    {
        const SLC_r64_t origin[4] = { _0, _0, _0, _1 };
        SLC_r64_t camera_lookAt_vector[4];
        SLC_Vecr64_Vector(camera_lookAt_vector, arg->cameraIsAt, arg->lookAt);
        const SLC_r64_t lookAt_ref[4] = {
             _0, _0, 
             -SLC_r64sqrt(SLC_Vecr64_InnerProduct(camera_lookAt_vector, camera_lookAt_vector)), 
             _1 };
        SLC_CTMatr64_t mpos = SLC_Camerar64_Position(arg, mpos_);
        SLC_CPntr64_t cameraIsAt_transformed = SLC_TMatr64_Transform(mpos, arg->cameraIsAt, cameraIsAt_transformed_);
        SLC_CPntr64_t lookAt_transformed = SLC_TMatr64_Transform(mpos, arg->lookAt, lookAt_transformed_);
        if (!SLC_Pntr64_areequal(origin, cameraIsAt_transformed, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Pntr64_areequal(lookAt_ref, lookAt_transformed, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_CameraOrthUT(SLC_PCTestArgs_t args)
{
    const SLC_r64_t _0 = SLC_r64_units[0], _1 = SLC_r64_units[1], _minus1 = SLC_r64_units[2];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCProjectionr64_t proj = args->data;
    const SLC_4r64_t 
        projected_left_bottom_far_ref = { _minus1, _minus1, _minus1, _1 },
        projected_right_top_near_ref = { _1, _1, _1, _1 };
    for (int i = 0; i < 2; i++, proj++)
    {
        SLC_r64_t workPnt[4], workMat[16];
        SLC_CTMatr64_t projMat = SLC_Camerar64_Orth(proj, workMat);
        SLC_r64_t xLeft = -proj->width_height[0]/(2 * _1);
        SLC_r64_t yBottom = -proj->width_height[1]/(2 * _1);
        SLC_r64_t zFar = proj->far_near[0];
        SLC_r64_t zNear = proj->far_near[1];
        const SLC_4r64_t
            left_bottom_far = { xLeft, yBottom, zFar, _1 },
            right_top_near = { -xLeft, -yBottom, zNear, _1 };
        fprintf(stderr, "--- projMat =\n");
        SLC_TMatr64_Print(stderr, projMat);
        SLC_CPntr64_t projected = SLC_TMatr64_Transform(projMat, left_bottom_far, workPnt);
        fprintf(stderr, "--- projected left_bottom_far = ");
        SLC_Pntr64_Print(stderr, projected);
        if (!SLC_Pntr64_areequal(
            projected_left_bottom_far_ref, projected, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        projected = SLC_TMatr64_Transform(projMat, right_top_near, workPnt);
        fprintf(stderr, "--- projected right_top_near = ");
        SLC_Pntr64_Print(stderr, projected);
        if (!SLC_Pntr64_areequal(
            projected_right_top_near_ref, projected, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}


SLC_errno_t SLC_r64_CameraPersUT(SLC_PCTestArgs_t args)
{
    const SLC_r64_t _0 = SLC_r64_units[0], _1 = SLC_r64_units[1], _minus1 = SLC_r64_units[2];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PCProjectionr64_t proj = args->data;
    SLC_r64_t workmat[16], workpnt[4];
    for (int i = 0; i < 2; i++, proj++)
    {
        SLC_r64_t xLeft = -proj->width_height[0]/((SLC_r64_t)2);
        SLC_r64_t yBottom = -proj->width_height[1]/((SLC_r64_t)2);
        SLC_r64_t zFar = proj->far_near[0], zNear = proj->far_near[1];
        SLC_r64_t zRatio = zFar/zNear;
        const SLC_4r64_t
            left_bottom_far = { zRatio * xLeft, zRatio * yBottom, zFar, _1 },
            right_top_near = { -xLeft, -yBottom, zNear, _1 },
            center_far = { _0, _0, zFar, _1 },
            center_near = { _0, _0, zNear, _1 };
        SLC_CTMatr64_t projmat = SLC_Camerar64_Perspective(proj, workmat);
        //printf("--- projmat = \n"); SLC_TMatr64_Print(stdout, projmat);
        {
            const SLC_4r64_t transformed_ref = { -_1, -_1, -_1, _1 };
            SLC_CPntr64_t transformed = SLC_TMatr64_Transform(projmat, left_bottom_far, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr64_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr64_Print(stdout, transformed);
            if (!SLC_Pntr64_areequal(transformed_ref, transformed, SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
        {
            const SLC_4r64_t transformed_ref = { _1, _1, _1, _1 };
            SLC_CPntr64_t transformed = SLC_TMatr64_Transform(projmat, right_top_near, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr64_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr64_Print(stdout, transformed);
            if (!SLC_Pntr64_areequal(transformed_ref, transformed, SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
        {
            const SLC_4r64_t transformed_ref = { _0, _0, -_1, _1 };
            SLC_CPntr64_t transformed = SLC_TMatr64_Transform(projmat, center_far, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr64_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr64_Print(stdout, transformed);
            if (!SLC_Pntr64_areequal(transformed_ref, transformed, SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
        {
            const SLC_4r64_t transformed_ref = { _0, _0, _1, _1 };
            SLC_CPntr64_t transformed = SLC_TMatr64_Transform(projmat, center_near, workpnt);
            //printf("--- transformed_ref = "); SLC_Pntr64_Print(stdout, transformed_ref);
            //printf("--- transformed = "); SLC_Pntr64_Print(stdout, transformed);
            if (!SLC_Pntr64_areequal(transformed_ref, transformed, SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    }
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Polar-Y__Cartesian__Conversion_r64
static const CameraUTPolarYDatar32_t _polarYr32_ref =
{
    { 1.0f, 0.0f, 0.0f, 1.0f }, // Nx
    { 0.0001f, 1.0f, 0.0f, 1.0f }, // Ny
    { 0.0f, 0.0f, 1.0f, 1.0f }, // Nz
    { 1.0f, 0.0f, 1.0f, 0.0f, 1.0f }, // Nx in Polar-Y
    { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f }, // Ny in polar-Y
    { 1.0f, 1.0f, 0.0f, 0.0f, 1.0f } // Nz in polar-Y
};

static const CameraUTPolarYDatar64_t _polarYr64_ref =
{
    { 1.0, 0.0, 0.0, 1.0 }, // Nx
    { 0.0000001, 1.0, 0.0, 1.0 }, // Ny
    { 0.0, 0.0, 1.0, 1.0 }, // Nz
    { 1.0, 0.0, 1.0, 0.0, 1.0 }, // Nx in Polar-Y
    { 1.0, 0.0, 1.0, 1.0, 0.0 }, // Ny in polar-Y
    { 1.0, 1.0, 0.0, 0.0, 1.0 } // Nz in polar-Y
};

static const SLC_CameraPositionr32_t _cameraPosr32[] =
{
    {
        { 1.0f, 1.1f, 0.9f, 1.0f }, // CameraIsAt
        { -1.0f, -1.1f, -1.1f, 1.0f }, // CameraLooksAt
        { 0.7071f, -0.7071f }
    },
    {
        { 1.0f, 1.1f, 0.9f, -1.0f }, // CameraIsAt
        { -1.0f, -1.1f, -1.1f, 1.0f }, // CameraLooksAt
        { 0.0f, 1.0f }
    },
    {
        { -1.0f, 1.1f, 0.9f, 1.0f }, // CameraIsAt
        { -1.0f, 1.1f, -1.1f, 1.0f }, // CameraLooksAt
        { -1.0f, 0.0f }
    },
    {
        { 1.0f, -1.1f, 0.9f, -1.0f }, // CameraIsAt
        { 1.0f, -1.1f, 1.1f, 1.0f }, // CameraLooksAt
        { 0.0f, -1.0f }
    }
};

static const SLC_CameraPositionr64_t _cameraPosr64[] =
{
    {
        { 1.0, 1.1, 0.9, 1.0 }, // CameraIsAt
        { -1.0, -1.1, -1.1, 1.0 }, // CameraLooksAt
        { 0.7071, -0.7071 }
    },
    {
        { 1.0, 1.1, 0.9, -1.0 }, // CameraIsAt
        { -1.0, -1.1, -1.1, 1.0 }, // CameraLooksAt
        { 0.0, 1.0 }
    },
    {
        { -1.0, 1.1, 0.9, 1.0 }, // CameraIsAt
        { -1.0, 1.1, -1.1, 1.0 }, // CameraLooksAt
        { -1.0, 0.0 }
    },
    {
        { 1.0, -1.1, 0.9, -1.0 }, // CameraIsAt
        { 1.0, -1.1, 1.1, 1.0 }, // CameraLooksAt
        { 0.0, -1.0 }
    }
};

static const SLC_Projectionr32_t  _orthr32[] =
{
    {
        { 640.0f, 480.0f }, // width_height
        { -1000.0f, -500.0f } // far_near
    },
    {
        { 0.1f, 0.07f }, // width_height
        { -1.0f, -0.8f }, // far_near
    }
};

static const SLC_Projectionr64_t  _orthr64[] =
{
    {
        { 640.0, 480.0 }, // width_height
        { -1000.0, -500.0 } // far_near
    },
    {
        { 0.1, 0.07 }, // width_height
        { -1.0, -0.8 }, // far_near
    }
};

SLC_errno_t SLC_CameraUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_TestArgs_t testargs32 = { 0, &_polarYr32_ref }, testargs64 = { 0, &_polarYr64_ref };
    do {
        // polar-Y <==> cartesian conversion
        SLC_test2(err, SLC_r32_PolarYUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_PolarYUT, &testargs64, __func__, __LINE__);

        // camera direction transform
        testargs32.data = _cameraPosr32;
        testargs64.data = _cameraPosr64;
        SLC_test2(err, SLC_r32_CameraDirectionUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_CameraDirectionUT, &testargs64, __func__, __LINE__);

        // camera position matrix
        SLC_test2(err, SLC_r32_CameraPositionUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_CameraPositionUT, &testargs64, __func__, __LINE__);

        // Orth-normal projection
        testargs32.data = _orthr32;
        testargs64.data = _orthr64;
        SLC_test2(err, SLC_r32_CameraOrthUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_CameraOrthUT, &testargs64, __func__, __LINE__);

        // Perspective projection
        SLC_test2(err, SLC_r32_CameraPersUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_CameraPersUT, &testargs64, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
