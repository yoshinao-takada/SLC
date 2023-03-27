#include "SLC/SLC_Geometry.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <assert.h>

#pragma region Unit_Tests_for_Geometry_functions_with_base_number_type_SLC_r32_t
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
SLC_errno_t SLC_r64_GeometryUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_Tests_for_Geometry_functions_with_base_number_type_SLC_r64_t
#pragma region r32_test_data
static const struct {

} r32_params;
#pragma endregion
#pragma region r64_test_data
static const struct {

} r64_params;
#pragma endregion

static const SLC_TestArgs_t r32_args = { 0, (void*)&r32_params };
static const SLC_TestArgs_t r64_args = { 0, (void*)&r64_params };


SLC_errno_t SLC_GeometryUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r32_GeometryUT, &r32_args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_GeometryUT, &r64_args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
