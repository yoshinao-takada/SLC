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
    do {
        // get inv mat0
        const SLC_TMatr32_t matinv = SLC_TMatr32_Inv(params->mat0, _matinv);

        // get (inv mat0) * mat0

        // compare identity matrix and the product (inv mat0) * mat0.
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_GeometryUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        
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
    do {
        // get inv mat0
        const SLC_TMatr64_t matinv = SLC_TMatr64_Inv(params->mat0, _matinv);

        // get (inv mat0) * mat0

        // compare identity matrix and the product (inv mat0) * mat0.
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_GeometryUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        
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


SLC_errno_t SLC_GeometryUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_TestArgs_t testargs32 = { 0, &r32_args }, testargs64 = { 0, &r64_args };
    do {
        SLC_test2(err, SLC_r32_GeometryUT, &testargs32, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryUT, &testargs64, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
