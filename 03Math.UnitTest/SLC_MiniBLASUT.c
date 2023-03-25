#include "SLC/SLC_MiniBLAS.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <assert.h>

#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r32_t
SLC_errno_t SLC_r32_MiniBLASUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r32_t
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r64_t
SLC_errno_t SLC_r64_MiniBLASUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r64_t
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c64_t
SLC_errno_t SLC_c64_MiniBLASUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c64_t
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c128_t
SLC_errno_t SLC_c128_MiniBLASUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c128_t
SLC_errno_t SLC_MiniBLASUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_r32_MiniBLASUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r64_MiniBLASUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c64_MiniBLASUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c128_MiniBLASUT, settings, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
