#include "SLC/SLC_Geometry.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <assert.h>

#pragma region Unit_Tests_for_Geometry_functions_with_base_number_type_SLC_r32_t
typedef struct {
    SLC_r32_t mat0[16], pnts[4*3], ref_transformed[4*3];
} GeometryUTr32_Params_t, *PGeometryUTr32_Params_t;
typedef const GeometryUTr32_Params_t *PCGeometryUTr32_Params_t;

SLC_errno_t SLC_r32_GeometryInvMulUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCGeometryUTr32_Params_t params = (PCGeometryUTr32_Params_t)args->data;
    SLC_TMatr32_t _matinv = (SLC_TMatr32_t)alloca(sizeof(SLC_r32_t) * 16);
    SLC_Pntr32_t _transformed = 
        (SLC_TMatr32_t)alloca(sizeof(SLC_r32_t) * 4 * 3);
    SLC_TMatr32_t _matinv_mat0 = (SLC_TMatr32_t)alloca(sizeof(SLC_r32_t) * 16);
    SLC_CTMatr32_t imat = SLC_TMatr32_IMat();
    do {
        // get inv mat0
        SLC_CTMatr32_t matinv = SLC_TMatr32_Inv((SLC_CTMatr32_t)params->mat0, _matinv);

        // get (inv mat0) * mat0
        SLC_CTMatr32_t matinv_mat0 = SLC_TMatr32_Mul(
            matinv, (SLC_CTMatr32_t)params->mat0, _matinv_mat0);

        // compare identity matrix and the product (inv mat0) * mat0.
        for (int i = 0; i < 16; i++)
        {
            if (!SLC_r32_areequal(imat[i], _matinv_mat0[i], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }

        // transform params->pnts
        for (int i = 0; i < 3; i++)
        {
            SLC_size_t offset = i * 4;
            SLC_TMatr32_Transform(params->mat0, params->pnts + offset, _transformed + offset);
        }
        for (int i = 0; i < 3; i++)
        {
            SLC_size_t offset = i * 4;
            if (!SLC_r32_areequal
                ((params->ref_transformed + offset)[0], (_transformed + offset)[0], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryRotateXUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r32_t mrot[16];
    SLC_r32_t uvecY[4] = { SLC_r32_units[0], SLC_r32_units[1], SLC_r32_units[0], SLC_r32_units[1] },
                rotated1[4], rotated2[4], rotated3[4];
    do {
        // rotation around X-axis
        SLC_CTMatr32_t m = SLC_TMatr32_rotateXdeg((SLC_r32_t)30, mrot);        
        SLC_CVecr32_t _rotated = 
            SLC_TMatr32_Transform(m, 
                SLC_TMatr32_Transform(m,
                    SLC_TMatr32_Transform(m, uvecY, rotated1),
                rotated2),
            rotated3);
        if ((const void*)_rotated != (const void*)rotated3)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[0], _rotated[0], SLC_r32_stdtol)) // x == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[0], _rotated[1], SLC_r32_stdtol)) // y == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[1], _rotated[2], SLC_r32_stdtol)) // z == 1
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryRotateYUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r32_t mrot[16];
    SLC_r32_t uvecZ[4] = { SLC_r32_units[0], SLC_r32_units[0], SLC_r32_units[1], SLC_r32_units[1] },
                rotated1[4], rotated2[4];
    do {
        // rotation around Y-axis
        SLC_CTMatr32_t m = SLC_TMatr32_rotateYdeg((SLC_r32_t)45, mrot);
        SLC_CVecr32_t _rotated = 
            SLC_TMatr32_Transform(m,
                SLC_TMatr32_Transform(m, uvecZ, rotated1),
            rotated2);
        if ((const void*)_rotated != (const void*)rotated2)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[1], _rotated[0], SLC_r32_stdtol)) // x == 1
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[0], _rotated[1], SLC_r32_stdtol)) // y == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[0], _rotated[2], SLC_r32_stdtol)) // z == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryRotateZUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r32_t mrot[16];
    SLC_r32_t uvecX[4] = { SLC_r32_units[1], SLC_r32_units[0], SLC_r32_units[0], SLC_r32_units[1] },
                rotated1[4], rotated2[4];
    do {
        // rotation around Z-axis
        SLC_CTMatr32_t m = SLC_TMatr32_rotateZdeg((SLC_r32_t)45, mrot);
        SLC_CVecr32_t _rotated = 
            SLC_TMatr32_Transform(m,
                SLC_TMatr32_Transform(m, uvecX, rotated1),
            rotated2);
        if ((const void*)_rotated != (const void*)rotated2)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[0], _rotated[0], SLC_r32_stdtol)) // x == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[1], _rotated[1], SLC_r32_stdtol)) // y == 1
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r32_areequal(SLC_r32_units[0], _rotated[2], SLC_r32_stdtol)) // z == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r32_GeometryInvMulUT, args, __func__, __LINE__);
        SLC_test(err, SLC_r32_GeometryRotateXUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r32_GeometryRotateYUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r32_GeometryRotateZUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

typedef struct {
    SLC_4r32_t isInPlane, isInLine, isNotIn;
    SLC_LinePlaner32_t linePlanes[3];
} SLC_LinePlaner32_TestParams_t, *SLC_PLinePlaner32_TestParams_t;
typedef const SLC_LinePlaner32_TestParams_t *SLC_PCLinePlaner32_TestParams_t;

SLC_errno_t SLC_r32_GeometryHLIsInLineUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner32_TestParams_t params = (SLC_PCLinePlaner32_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_bool_t isIn =
            SLC_Liner32_IsIn(&params->linePlanes[0], params->isInLine, SLC_r32_stdtol);
        if (!isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        isIn = SLC_Liner32_IsIn(&params->linePlanes[0], params->isNotIn, SLC_r32_stdtol);
        if (isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryHLIsInPlaneUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner32_TestParams_t params = (SLC_PCLinePlaner32_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_bool_t isIn =
            SLC_Planer32_IsIn(&params->linePlanes[0], params->isInPlane, SLC_r32_stdtol);
        if (!isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        isIn = SLC_Planer32_IsIn(&params->linePlanes[0], params->isNotIn, SLC_r32_stdtol);
        if (isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryHLLinePlaneCrosssectionUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner32_TestParams_t params = (SLC_PCLinePlaner32_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_4r32_t crosssection;
        if (EXIT_SUCCESS != (err = SLC_LinePlaner32_Crosssection(&params->linePlanes[0], &params->linePlanes[1], crosssection)))
        {
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_r32_t tol = (SLC_r32_t)10 * SLC_r32_stdtol;
        if (!SLC_Liner32_IsIn(&params->linePlanes[0], crosssection, tol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer32_IsIn(&params->linePlanes[1], crosssection, tol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryHL3PlaneCrosssectionUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner32_TestParams_t params = (SLC_PCLinePlaner32_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_4r32_t crosssection;
        if (EXIT_SUCCESS != (err = SLC_Planer32_3Crosssection(params->linePlanes, crosssection)))
        {
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer32_IsIn(&params->linePlanes[0], crosssection, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer32_IsIn(&params->linePlanes[1], crosssection, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer32_IsIn(&params->linePlanes[2], crosssection, SLC_r32_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryHL2PlaneCrosssectionUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner32_TestParams_t params = (SLC_PCLinePlaner32_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    const SLC_r32_t _1 = SLC_r32_units[1], _minus1 = SLC_r32_units[2];
    const SLC_r32_t As[] = { _1, _minus1, _1 + _minus1, _1 - _minus1 };
    do {
        SLC_LinePlaner32_t crosssection;
        SLC_4r32_t pnt;
        if (EXIT_SUCCESS != (err = SLC_Planer32_2Crosssection(params->linePlanes, &crosssection)))
        {
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(As); i++)
        {
            SLC_r32_t A = As[i];
            SLC_r32_t normalizerP0 = crosssection.p0[3];
            SLC_r32_t normalizerV0 = crosssection.v0[3];
            SLC_4r32_t pnt = 
            {
                normalizerP0 * crosssection.p0[0] + A * normalizerV0 * crosssection.v0[0],
                normalizerP0 * crosssection.p0[1] + A * normalizerV0 * crosssection.v0[1],
                normalizerP0 * crosssection.p0[2] + A * normalizerV0 * crosssection.v0[2],
                _1
            };
            SLC_bool_t isIn = SLC_Planer32_IsIn(&params->linePlanes[0], pnt, SLC_r32_stdtol);
            if (!isIn)
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

// unit test function for Geometry High-Level APIs
SLC_errno_t SLC_r32_GeometryHLAPIUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r32_GeometryHLIsInLineUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_GeometryHLIsInPlaneUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_GeometryHLLinePlaneCrosssectionUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_GeometryHL3PlaneCrosssectionUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_GeometryHL2PlaneCrosssectionUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_Tests_for_Geometry_functions_with_base_number_type_SLC_r32_t
#pragma region Unit_Tests_for_Geometry_functions_with_base_number_type_SLC_r64_t
typedef struct {
    SLC_r64_t mat0[16], pnts[4*3], ref_transformed[4*3];
} GeometryUTr64_Params_t, *PGeometryUTr64_Params_t;
typedef const GeometryUTr64_Params_t *PCGeometryUTr64_Params_t;

SLC_errno_t SLC_r64_GeometryInvMulUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCGeometryUTr64_Params_t params = (PCGeometryUTr64_Params_t)args->data;
    SLC_TMatr64_t _matinv = (SLC_TMatr64_t)alloca(sizeof(SLC_r64_t) * 16);
    SLC_Pntr64_t _transformed = 
        (SLC_TMatr64_t)alloca(sizeof(SLC_r64_t) * 4 * 3);
    SLC_TMatr64_t _matinv_mat0 = (SLC_TMatr64_t)alloca(sizeof(SLC_r64_t) * 16);
    SLC_CTMatr64_t imat = SLC_TMatr64_IMat();
    do {
        // get inv mat0
        SLC_CTMatr64_t matinv = SLC_TMatr64_Inv((SLC_CTMatr64_t)params->mat0, _matinv);

        // get (inv mat0) * mat0
        SLC_CTMatr64_t matinv_mat0 = SLC_TMatr64_Mul(
            matinv, (SLC_CTMatr64_t)params->mat0, _matinv_mat0);

        // compare identity matrix and the product (inv mat0) * mat0.
        for (int i = 0; i < 16; i++)
        {
            if (!SLC_r64_areequal(imat[i], _matinv_mat0[i], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }

        // transform params->pnts
        for (int i = 0; i < 3; i++)
        {
            SLC_size_t offset = i * 4;
            SLC_TMatr64_Transform(params->mat0, params->pnts + offset, _transformed + offset);
        }
        for (int i = 0; i < 3; i++)
        {
            SLC_size_t offset = i * 4;
            if (!SLC_r64_areequal
                ((params->ref_transformed + offset)[0], (_transformed + offset)[0], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryRotateXUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r64_t mrot[16];
    SLC_r64_t uvecY[4] = { SLC_r64_units[0], SLC_r64_units[1], SLC_r64_units[0], SLC_r64_units[1] },
                rotated1[4], rotated2[4], rotated3[4];
    do {
        // rotation around X-axis
        SLC_CTMatr64_t m = SLC_TMatr64_rotateXdeg((SLC_r64_t)30, mrot);        
        SLC_CVecr64_t _rotated = 
            SLC_TMatr64_Transform(m, 
                SLC_TMatr64_Transform(m,
                    SLC_TMatr64_Transform(m, uvecY, rotated1),
                rotated2),
            rotated3);
        if ((const void*)_rotated != (const void*)rotated3)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[0], _rotated[0], SLC_r64_stdtol)) // x == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[0], _rotated[1], SLC_r64_stdtol)) // y == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[1], _rotated[2], SLC_r64_stdtol)) // z == 1
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryRotateYUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r64_t mrot[16];
    SLC_r64_t uvecZ[4] = { SLC_r64_units[0], SLC_r64_units[0], SLC_r64_units[1], SLC_r64_units[1] },
                rotated1[4], rotated2[4];
    do {
        // rotation around Y-axis
        SLC_CTMatr64_t m = SLC_TMatr64_rotateYdeg((SLC_r64_t)45, mrot);
        SLC_CVecr64_t _rotated = 
            SLC_TMatr64_Transform(m,
                SLC_TMatr64_Transform(m, uvecZ, rotated1),
            rotated2);
        if ((const void*)_rotated != (const void*)rotated2)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[1], _rotated[0], SLC_r64_stdtol)) // x == 1
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[0], _rotated[1], SLC_r64_stdtol)) // y == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[0], _rotated[2], SLC_r64_stdtol)) // z == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryRotateZUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r64_t mrot[16];
    SLC_r64_t uvecX[4] = { SLC_r64_units[1], SLC_r64_units[0], SLC_r64_units[0], SLC_r64_units[1] },
                rotated1[4], rotated2[4];
    do {
        // rotation around Z-axis
        SLC_CTMatr64_t m = SLC_TMatr64_rotateZdeg((SLC_r64_t)45, mrot);
        SLC_CVecr64_t _rotated = 
            SLC_TMatr64_Transform(m,
                SLC_TMatr64_Transform(m, uvecX, rotated1),
            rotated2);
        if ((const void*)_rotated != (const void*)rotated2)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[0], _rotated[0], SLC_r64_stdtol)) // x == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[1], _rotated[1], SLC_r64_stdtol)) // y == 1
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_r64_areequal(SLC_r64_units[0], _rotated[2], SLC_r64_stdtol)) // z == 0
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r64_GeometryInvMulUT, args, __func__, __LINE__);
        SLC_test(err, SLC_r64_GeometryRotateXUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r64_GeometryRotateYUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r64_GeometryRotateZUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

typedef struct {
    SLC_4r64_t isInPlane, isInLine, isNotIn;
    SLC_LinePlaner64_t linePlanes[3];
} SLC_LinePlaner64_TestParams_t, *SLC_PLinePlaner64_TestParams_t;
typedef const SLC_LinePlaner64_TestParams_t *SLC_PCLinePlaner64_TestParams_t;

SLC_errno_t SLC_r64_GeometryHLIsInLineUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner64_TestParams_t params = (SLC_PCLinePlaner64_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_bool_t isIn =
            SLC_Liner64_IsIn(&params->linePlanes[0], params->isInLine, SLC_r64_stdtol);
        if (!isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        isIn = SLC_Liner64_IsIn(&params->linePlanes[0], params->isNotIn, SLC_r64_stdtol);
        if (isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryHLIsInPlaneUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner64_TestParams_t params = (SLC_PCLinePlaner64_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_bool_t isIn =
            SLC_Planer64_IsIn(&params->linePlanes[0], params->isInPlane, SLC_r64_stdtol);
        if (!isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        isIn = SLC_Planer64_IsIn(&params->linePlanes[0], params->isNotIn, SLC_r64_stdtol);
        if (isIn)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryHLLinePlaneCrosssectionUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner64_TestParams_t params = (SLC_PCLinePlaner64_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_4r64_t crosssection;
        if (EXIT_SUCCESS != (err = SLC_LinePlaner64_Crosssection(&params->linePlanes[0], &params->linePlanes[1], crosssection)))
        {
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        SLC_r64_t tol = (SLC_r64_t)10 * SLC_r64_stdtol;
        if (!SLC_Liner64_IsIn(&params->linePlanes[0], crosssection, tol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer64_IsIn(&params->linePlanes[1], crosssection, tol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryHL3PlaneCrosssectionUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner64_TestParams_t params = (SLC_PCLinePlaner64_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_4r64_t crosssection;
        if (EXIT_SUCCESS != (err = SLC_Planer64_3Crosssection(params->linePlanes, crosssection)))
        {
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer64_IsIn(&params->linePlanes[0], crosssection, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer64_IsIn(&params->linePlanes[1], crosssection, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        if (!SLC_Planer64_IsIn(&params->linePlanes[2], crosssection, SLC_r64_stdtol))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryHL2PlaneCrosssectionUT(SLC_PCTestArgs_t args)
{
    SLC_PCLinePlaner64_TestParams_t params = (SLC_PCLinePlaner64_TestParams_t)args->data;
    SLC_errno_t err = EXIT_SUCCESS;
    const SLC_r64_t _1 = SLC_r64_units[1], _minus1 = SLC_r64_units[2];
    const SLC_r64_t As[] = { _1, _minus1, _1 + _minus1, _1 - _minus1 };
    do {
        SLC_LinePlaner64_t crosssection;
        SLC_4r64_t pnt;
        if (EXIT_SUCCESS != (err = SLC_Planer64_2Crosssection(params->linePlanes, &crosssection)))
        {
            SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
            break;
        }
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(As); i++)
        {
            SLC_r64_t A = As[i];
            SLC_r64_t normalizerP0 = crosssection.p0[3];
            SLC_r64_t normalizerV0 = crosssection.v0[3];
            SLC_4r64_t pnt = 
            {
                normalizerP0 * crosssection.p0[0] + A * normalizerV0 * crosssection.v0[0],
                normalizerP0 * crosssection.p0[1] + A * normalizerV0 * crosssection.v0[1],
                normalizerP0 * crosssection.p0[2] + A * normalizerV0 * crosssection.v0[2],
                _1
            };
            SLC_bool_t isIn = SLC_Planer64_IsIn(&params->linePlanes[0], pnt, SLC_r64_stdtol);
            if (!isIn)
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

// unit test function for Geometry High-Level APIs
SLC_errno_t SLC_r64_GeometryHLAPIUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r64_GeometryHLIsInLineUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryHLIsInPlaneUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryHLLinePlaneCrosssectionUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryHL3PlaneCrosssectionUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryHL2PlaneCrosssectionUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_Tests_for_Geometry_functions_with_base_number_type_SLC_r64_t
static const GeometryUTr32_Params_t r32_args = 
{
    { // mat0
        1.0f, 2.5f, 3.5f, 1.5f,
        -2.5f, 1.0f, 0.0f, -2.0f,
        3.5f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    },
    { // pnts
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
    },
    { // ref_transformed
        8.5f, -3.5f, 4.5f, 1.0f,
        6.5f, 1.5f, -2.5f, 1.0f,
        3.5f, -5.5f, 4.5f, 1.0f
    }
};
static const GeometryUTr64_Params_t r64_args = 
{
    { // mat0
        1.0, 2.5, 3.5, 1.5,
        -2.5, 1.0, 0.0, -2.0,
        3.5, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    },
    { // pnts
        1.0, 1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0, 1.0,
        1.0, -1.0, 1.0, 1.0,
    },
    { // ref_transformed
        8.5, -3.5, 4.5, 1.0,
        6.5, 1.5, -2.5, 1.0,
        3.5, -5.5, 4.5, 1.0
    }
};

static const SLC_LinePlaner32_TestParams_t r32_lineplane =
{
    // ref plane/line ref point is { 1.5, 1.5, 0.0 }, normal/direction vector = { 0.0, 0.0, -1.0, 1.0 }
    // coordinate in the test plane
    { 1.5f, -1.5f, 0.0f,  1.0f },
    // coordinate in the test line
    { 1.5f, 1.5f, 3.0f,  1.0f },
    // coordinate not in the test plane or the test line.
    { 1.2f, 1.5f, 1.0f,  1.0f },
    { // array of line or planes 
        // [0]: test plane and test line of IsIn methods, and
        // test line of line-plane crosssection and test plane of 2-plane, 3-plane crosssection
        {
            { 1.5f, 1.5f, 0.0f,  1.0f }, { 0.0f, 0.0f, -1.0f,  1.0f }
        },
        // [1]: test plane of line-plane crosssection and the 2nd plane of 2-plane, 3-plane crosssection
        {
            { 1.5f, 1.5f, 0.0f,  1.0f }, { 0.0f, 0.7071f, -.7071f,  1.0f }
        },
        // [2]: test plane of 3-plane crosssection
        {
            { 2.0f, -1.0f, 0.3f,  1.0f }, { 1.0f, 0.0f, 0.0f,  1.0f }
        }
    }
};
static const SLC_LinePlaner64_TestParams_t r64_lineplane =
{
    // ref plane/line ref point is { 1.5, 1.5, 0.0 }, normal/direction vector = { 0.0, 0.0, -1.0, 1.0 }
    // coordinate in the test plane
    { 1.5, -1.5, 0.0,  1.0 },
    // coordinate in the test line
    { 1.5, 1.5, 3.0,  1.0 },
    // coordinate not in the test plane or the test line.
    { 1.2, 1.5, 1.0,  1.0 },
    { // array of line or planes 
        // [0]: test plane and test line of IsIn methods, and
        // test line of line-plane crosssection and test plane of 2-plane, 3-plane crosssection
        {
            { 1.5, 1.5, 0.0,  1.0 }, { 0.0, 0.0, -1.0,  1.0 }
        },
        // [1]: test plane of line-plane crosssection and the 2nd plane of 2-plane, 3-plane crosssection
        {
            { 1.5, 1.5, 0.0,  1.0 }, { 0.0, 0.7071, -.7071,  1.0 }
        },
        // [2]: test plane of 3-plane crosssection
        {
            { 2.0, -1.0, 0.3,  1.0 }, { 1.0, 0.0, 0.0,  1.0 }
        }
    }
};

SLC_errno_t SLC_GeometryUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_TestArgs_t testargs32 = { 0, &r32_args }, testargs64 = { 0, &r64_args };
    do {
        SLC_test2(err, SLC_r32_GeometryUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryUT, &testargs64, __func__, __LINE__);
        testargs32.data = &r32_lineplane;
        testargs64.data = &r64_lineplane;
        SLC_test2(err, SLC_r32_GeometryHLAPIUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryHLAPIUT, &testargs64, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
