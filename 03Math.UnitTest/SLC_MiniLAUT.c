#include "SLC/SLC_MiniLA.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_NumbersCopy.h"
#include <assert.h>

#pragma region Unit_tests_for_MiniLA_with_base_number_type_SLC_r32_t
#pragma region basic_matrix_operations
typedef struct {
    SLC_4i16_t size;
    SLC_r32_t mat0[16], mat1[16];
    SLC_r32_t matsum[16], matprod[16], scaled[16], scaledsum[16];
    SLC_r32_t mattranspose[16], matinv[16];
    SLC_r32_t tolerance;
    SLC_r32_t scale0, scale1;
} r32_MiniLAUTParams_t, *r32_PMiniLAUTParams_t;
typedef const r32_MiniLAUTParams_t *r32_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matr32_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matsum = SLC_Array_Alloca(params->size);
    do {
        SLC_r32_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_r32_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matr32_Add(matsum, mat0, mat1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_r32_areequal(params->matsum[index], matsum->data._r32[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    free(mat0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr32_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matScaleAdd = SLC_Array_Alloca(params->size);
    do {
        SLC_r32_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_r32_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matr32_ScaleAdd(matScaleAdd, mat0, &params->scale0, mat1, &params->scale1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_r32_areequal(params->scaledsum[index], matScaleAdd->data._r32[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    free(mat0);
    return err;
}

SLC_errno_t SLC_Matr32_ScaleUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr32_MulUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr32_TransposeUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr32_TransConjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr32_InvUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_MiniLAUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {
        SLC_test2(err, SLC_Matr32_AddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matr32_ScaleAddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matr32_ScaleUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion basic_matrix_operations
#pragma region linear_equation_solvers
typedef struct {
    SLC_r32_t matL[16], matR[16], matLredundant[24];
    SLC_r32_t matX[16]; // solution
} r32_MiniLASolverUTParams_t, *r32_PMiniLASolverUTParams_t;
typedef const r32_MiniLASolverUTParams_t *r32_PCMiniLASolverUTParams_t;

SLC_errno_t SLC_r32_MiniLASolverUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLASolverUTParams_t params = (r32_PCMiniLASolverUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion linear_equation_solvers
#pragma endregion Unit_tests_for_MiniLA_with_base_number_type_SLC_r32_t
#pragma region Unit_tests_for_MiniLA_with_base_number_type_SLC_r64_t
#pragma region basic_matrix_operations
typedef struct {
    SLC_4i16_t size;
    SLC_r64_t mat0[16], mat1[16];
    SLC_r64_t matsum[16], matprod[16], scaled[16], scaledsum[16];
    SLC_r64_t mattranspose[16], matinv[16];
    SLC_r64_t tolerance;
    SLC_r64_t scale0, scale1;
} r64_MiniLAUTParams_t, *r64_PMiniLAUTParams_t;
typedef const r64_MiniLAUTParams_t *r64_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matr64_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matsum = SLC_Array_Alloca(params->size);
    do {
        SLC_r64_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_r64_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matr64_Add(matsum, mat0, mat1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_r64_areequal(params->matsum[index], matsum->data._r64[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    free(mat0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr64_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matScaleAdd = SLC_Array_Alloca(params->size);
    do {
        SLC_r64_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_r64_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matr64_ScaleAdd(matScaleAdd, mat0, &params->scale0, mat1, &params->scale1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_r64_areequal(params->scaledsum[index], matScaleAdd->data._r64[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    free(mat0);
    return err;
}

SLC_errno_t SLC_Matr64_ScaleUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr64_MulUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr64_TransposeUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr64_TransConjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr64_InvUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_MiniLAUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {
        SLC_test2(err, SLC_Matr64_AddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matr64_ScaleAddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matr64_ScaleUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion basic_matrix_operations
#pragma region linear_equation_solvers
typedef struct {
    SLC_r64_t matL[16], matR[16], matLredundant[24];
    SLC_r64_t matX[16]; // solution
} r64_MiniLASolverUTParams_t, *r64_PMiniLASolverUTParams_t;
typedef const r64_MiniLASolverUTParams_t *r64_PCMiniLASolverUTParams_t;

SLC_errno_t SLC_r64_MiniLASolverUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLASolverUTParams_t params = (r64_PCMiniLASolverUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion linear_equation_solvers
#pragma endregion Unit_tests_for_MiniLA_with_base_number_type_SLC_r64_t
#pragma region Unit_tests_for_MiniLA_with_base_number_type_SLC_c64_t
#pragma region basic_matrix_operations
typedef struct {
    SLC_4i16_t size;
    SLC_c64_t mat0[16], mat1[16];
    SLC_c64_t matsum[16], matprod[16], scaled[16], scaledsum[16];
    SLC_c64_t mattranspose[16], matinv[16];
    SLC_r32_t tolerance;
    SLC_c64_t scale0, scale1;
} c64_MiniLAUTParams_t, *c64_PMiniLAUTParams_t;
typedef const c64_MiniLAUTParams_t *c64_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matc64_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matsum = SLC_Array_Alloca(params->size);
    do {
        SLC_c64_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_c64_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matc64_Add(matsum, mat0, mat1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_c64_areequal(params->matsum[index], matsum->data._c64[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    free(mat0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc64_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matScaleAdd = SLC_Array_Alloca(params->size);
    do {
        SLC_c64_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_c64_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matc64_ScaleAdd(matScaleAdd, mat0, &params->scale0, mat1, &params->scale1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_c64_areequal(params->scaledsum[index], matScaleAdd->data._c64[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    free(mat0);
    return err;
}

SLC_errno_t SLC_Matc64_ScaleUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc64_MulUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc64_TransposeUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc64_TransConjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc64_InvUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_MiniLAUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {
        SLC_test2(err, SLC_Matc64_AddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matc64_ScaleAddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matc64_ScaleUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion basic_matrix_operations
#pragma region linear_equation_solvers
typedef struct {
    SLC_c64_t matL[16], matR[16], matLredundant[24];
    SLC_c64_t matX[16]; // solution
} c64_MiniLASolverUTParams_t, *c64_PMiniLASolverUTParams_t;
typedef const c64_MiniLASolverUTParams_t *c64_PCMiniLASolverUTParams_t;

SLC_errno_t SLC_c64_MiniLASolverUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLASolverUTParams_t params = (c64_PCMiniLASolverUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion linear_equation_solvers
#pragma endregion Unit_tests_for_MiniLA_with_base_number_type_SLC_c64_t
#pragma region Unit_tests_for_MiniLA_with_base_number_type_SLC_c128_t
#pragma region basic_matrix_operations
typedef struct {
    SLC_4i16_t size;
    SLC_c128_t mat0[16], mat1[16];
    SLC_c128_t matsum[16], matprod[16], scaled[16], scaledsum[16];
    SLC_c128_t mattranspose[16], matinv[16];
    SLC_r64_t tolerance;
    SLC_c128_t scale0, scale1;
} c128_MiniLAUTParams_t, *c128_PMiniLAUTParams_t;
typedef const c128_MiniLAUTParams_t *c128_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matc128_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matsum = SLC_Array_Alloca(params->size);
    do {
        SLC_c128_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_c128_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matc128_Add(matsum, mat0, mat1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_c128_areequal(params->matsum[index], matsum->data._c128[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    free(mat0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc128_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    SLC_PArray_t mat0 = SLC_Array_Alloc(params->size);
    SLC_PArray_t mat1 = SLC_Array_Alloca(params->size);
    SLC_PArray_t matScaleAdd = SLC_Array_Alloca(params->size);
    do {
        SLC_c128_copy(mat0->data._ptr, 1, params->mat0, 1, SLC_ARRAYSIZE(params->mat0));
        SLC_c128_copy(mat1->data._ptr, 1, params->mat1, 1, SLC_ARRAYSIZE(params->mat1));
        SLC_Matc128_ScaleAdd(matScaleAdd, mat0, &params->scale0, mat1, &params->scale1);
        SLC_i16_t rows = SLC_Array_MatRows(mat0), columns = SLC_Array_MatColumns(mat0);
        for (SLC_i16_t row=0; row < rows; row++)
        {
            for (SLC_i16_t column = 0; column < columns; column++)
            {
                SLC_size_t index = column + row * columns;
                if (!SLC_c128_areequal(params->scaledsum[index], matScaleAdd->data._c128[index], params->tolerance))
                {
                    err = EXIT_FAILURE;
                    SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    free(mat0);
    return err;
}

SLC_errno_t SLC_Matc128_ScaleUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc128_MulUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc128_TransposeUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc128_TransConjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc128_InvUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_MiniLAUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {
        SLC_test2(err, SLC_Matc128_AddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matc128_ScaleAddUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_Matc128_ScaleUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion basic_matrix_operations
#pragma region linear_equation_solvers
typedef struct {
    SLC_c128_t matL[16], matR[16], matLredundant[24];
    SLC_c128_t matX[16]; // solution
} c128_MiniLASolverUTParams_t, *c128_PMiniLASolverUTParams_t;
typedef const c128_MiniLASolverUTParams_t *c128_PCMiniLASolverUTParams_t;

SLC_errno_t SLC_c128_MiniLASolverUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLASolverUTParams_t params = (c128_PCMiniLASolverUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion linear_equation_solvers
#pragma endregion Unit_tests_for_MiniLA_with_base_number_type_SLC_c128_t
#pragma region basic_math_operation_test_data
r32_MiniLAUTParams_t r32_LAparams = {
    { sizeof(SLC_r32_t), 4, 4, 1 },
    { // mat0
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 3.0f, 4.0f, 1.0f,
        1.0f, 4.0f, 3.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    },
    { // mat1
        1.1f, 2.1f, 3.1f, 4.1f,
        2.0f, 3.0f, 4.0f, 1.0f,
        1.0f, 4.0f, 3.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    },
    { // matsum
        2.1f, 4.1f, 6.1f, 8.1f,
        4.0f, 6.0f, 8.0f, 2.0f,
        2.0f, 8.0f, 6.0f, 4.0f,
        8.0f, 6.0f, 4.0f, 2.0f
    },
    { // matprod
        24.1f, 32.1f, 28.1f, 16.1f,
        16.2f, 32.2f, 32.2f, 20.2f,
        20.1f, 32.1f, 32.1f, 16.1f,
        16.4f, 28.4f, 32.4f, 24.4f
    },
    { // scale0 * mat0
        2.3f, 4.6f, 6.9f, 9.2f,
        4.6f, 6.9f, 9.2f, 2.3f,
        2.3f, 9.2f, 6.9f, 4.6f,
        9.2f, 6.9f, 4.6f, 2.3f
    },
    { // scale0 * mat0 + scale1 * mat1
        0.65f, 1.45f, 2.25f, 3.05f,
        1.6f, 2.4f, 3.2f, 0.8f,
        0.8f, 3.2f, 2.4f, 1.6f,
        3.2f, 2.4f, 1.6f, 0.8f
    },
    { // transpose mat0
        1.0f, 2.0f, 1.0f, 4.0f,
        2.0f, 3.0f, 4.0f, 3.0f,
        3.0f, 4.0f, 3.0f, 2.0f,
        4.0f, 1.0f, 2.0f, 1.0f
    },
    { // inv mat0
        0.05f, 0.0f, -0.25f, 0.3f,
        -0.2f, -0.25f, 0.5f, 0.05f,
        0.05f, 0.5f, -0.25f, -0.2f,
        0.3f, -0.25f, 0.0f, 0.05f
    },
    SLC_r32_stdtol, 2.3f, -1.5f
};

r64_MiniLAUTParams_t r64_LAparams = {
    { sizeof(SLC_r64_t), 4, 4, 1 },
    { // mat0
        1.0, 2.0, 3.0, 4.0,
        2.0, 3.0, 4.0, 1.0,
        1.0, 4.0, 3.0, 2.0,
        4.0, 3.0, 2.0, 1.0
    },
    { // mat1
        1.1, 2.1, 3.1, 4.1,
        2.0, 3.0, 4.0, 1.0,
        1.0, 4.0, 3.0, 2.0,
        4.0, 3.0, 2.0, 1.0
    },
    { // matsum
        2.1, 4.1, 6.1, 8.1,
        4.0, 6.0, 8.0, 2.0,
        2.0, 8.0, 6.0, 4.0,
        8.0, 6.0, 4.0, 2.0
    },
    { // matprod
        24.1, 32.1, 28.1, 16.1,
        16.2, 32.2, 32.2, 20.2,
        20.1, 32.1, 32.1, 16.1,
        16.4, 28.4, 32.4, 24.4
    },
    { // scale * mat0
        2.3, 4.6, 6.9, 9.2,
        4.6, 6.9, 9.2, 2.3,
        2.3, 9.2, 6.9, 4.6,
        9.2, 6.9, 4.6, 2.3
    },
    { // scale0 * mat0 + scale1 * mat1
        0.65, 1.45, 2.25, 3.05,
        1.6, 2.4, 3.2, 0.8,
        0.8, 3.2, 2.4, 1.6,
        3.2, 2.4, 1.6, 0.8
    },
    { // transpose mat0
        1.0, 2.0, 1.0, 4.0,
        2.0, 3.0, 4.0, 3.0,
        3.0, 4.0, 3.0, 2.0,
        4.0, 1.0, 2.0, 1.0
    },
    { // inv mat0
        0.05, 0.0, -0.25, 0.3,
        -0.2, -0.25, 0.5, 0.05,
        0.05, 0.5, -0.25, -0.2,
        0.3, -0.25, 0.0, 0.05
    },
    SLC_r64_stdtol, 2.3, -1.5
};

c64_MiniLAUTParams_t c64_LAparams = {
    { sizeof(SLC_c64_t), 4, 4, 1 },
    { // mat0
        CMPLXF(1.0f,1.0f), CMPLXF(2.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(4.0f,-1.0f),
        CMPLXF(2.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(4.0f,-1.0f), CMPLXF(1.0f,1.0f),
        CMPLXF(1.0f,1.0f), CMPLXF(4.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(2.0f,-1.0f),
        CMPLXF(4.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(2.0f,-1.0f), CMPLXF(1.0f,1.0f)
    },
    { // mat1
        CMPLXF(1.1f,1.0f), CMPLXF(2.1f,-1.0f), CMPLXF(3.1f,1.0f), CMPLXF(4.1f,-1.0f),
        CMPLXF(2.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(4.0f,-1.0f), CMPLXF(1.0f,1.0f),
        CMPLXF(1.0f,1.0f), CMPLXF(4.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(2.0f,-1.0f),
        CMPLXF(4.0f,-1.0f), CMPLXF(3.0f,1.0f), CMPLXF(2.0f,-1.0f), CMPLXF(1.0f,1.0f)
    },
    { // matsum
        CMPLXF(2.1f,2.0f), CMPLXF(4.1f,-2.0f), CMPLXF(6.1f,2.0f), CMPLXF(8.1f,-2.0f),
        CMPLXF(4.0f,-2.0f),CMPLXF(6.0f,2.0f), CMPLXF(8.0f,-2.0f), CMPLXF(2.0f,2.0f),
        CMPLXF(2.0f,2.0f), CMPLXF(8.0f,-2.0f),CMPLXF(6.0f,2.0f), CMPLXF(4.0f,-2.0f),
        CMPLXF(8.0f,-2.0f), CMPLXF(6.0f,2.0f),CMPLXF(4.0f,-2.0f),CMPLXF(2.0f,2.0f)
    },
    { // matprod
        CMPLXF(20.1f,-5.9f), CMPLXF(36.1f,2.1f), CMPLXF(24.1f,-1.9f), CMPLXF(20.1f, 6.1f),
        CMPLXF(20.2f,5.9f), CMPLXF(28.2f,-2.1f), CMPLXF(36.2f,1.9f), CMPLXF(16.2f,-6.1f),
        CMPLXF(16.1f,-5.9f), CMPLXF(36.1f,2.1f), CMPLXF(28.1f,-1.9f), CMPLXF(20.1f,6.1f),
        CMPLXF(20.4f,5.9f), CMPLXF(24.4f,-2.1f), CMPLXF(36.4f,1.9f), CMPLXF(20.4f,-6.1f)
    },
    { // scale * mat0
        CMPLXF(3.8f,0.8f), CMPLXF(3.1f,-5.3f), CMPLXF(8.4f,-2.2f), CMPLXF(7.7f,-8.3f),
        CMPLXF(3.1f,-5.3f),CMPLXF(8.4f,-2.2f), CMPLXF(7.7f,-8.3f), CMPLXF(3.8f,0.8f),
        CMPLXF(3.8f,0.8f), CMPLXF(7.7f,-8.3f), CMPLXF(8.4f,-2.2f), CMPLXF(3.1f,-5.3f),
        CMPLXF(7.7f,-8.3f),CMPLXF(8.4f,-2.2f), CMPLXF(3.1f,-5.3f), CMPLXF(3.8f,0.8f)
    },
    { // scale0 * mat0 + scale1 * mat1
        CMPLXF(-0.4f,1.0f), CMPLXF(0.9f,0.9f), CMPLXF(0.2f,2.0f), CMPLXF(1.5f,1.9f),
        CMPLXF(1.1f,0.7f), CMPLXF(0.4f,1.8f), CMPLXF(1.7f,1.7f), CMPLXF(-0.2f,0.8f),
        CMPLXF(-0.2f,0.8f), CMPLXF(1.7f,1.7f), CMPLXF(0.4f,1.8f), CMPLXF(1.1f,0.7f),
        CMPLXF(1.7f,1.7f), CMPLXF(0.4f,1.8f), CMPLXF(1.1f,0.7f), CMPLXF(-0.2f,0.8f)
    },
    { // transpose mat0
        CMPLXF(1.0f,1.0f), CMPLXF(2.0f,-1.0f), CMPLXF(1.0f,1.0f), CMPLXF(4.0f,-1.0f),
        CMPLXF(2.0f,-1.0f),CMPLXF(3.0f,1.0f), CMPLXF(4.0f,-1.0f), CMPLXF(3.0f,1.0f),
        CMPLXF(3.0f,1.0f), CMPLXF(4.0f,-1.0f),CMPLXF(3.0f,1.0f), CMPLXF(2.0f,-1.0f),
        CMPLXF(4.0f,-1.0f),CMPLXF(1.0f,1.0f), CMPLXF(2.0f,-1.0f),CMPLXF(1.0f,1.0f)
    },
    { // inv mat0
        CMPLXF(0.05f,0.0f), CMPLXF(-0.2f,0.1f), CMPLXF(-0.05f,-0.1f), CMPLXF(0.3f,0.0f),
        CMPLXF(-0.2f,0.0f), CMPLXF(-0.05f,-0.1f), CMPLXF(0.3f,0.1f), CMPLXF(0.05f,0.0f),
        CMPLXF(0.05f,0.0f), CMPLXF(0.3f,0.1f), CMPLXF(-0.05f,-0.1f), CMPLXF(-0.2f,0.0f),
        CMPLXF(0.3f,0.0f), CMPLXF(-0.05f,-0.1f),CMPLXF(-0.2f,0.1f), CMPLXF(0.05f,0.0f)
    },
    SLC_c64_stdtol, CMPLXF(2.3f,-1.5f), CMPLXF(-2.0f,2.0f)
};

c128_MiniLAUTParams_t c128_LAparams = {
    { sizeof(SLC_c128_t), 4, 4, 1 },
    { // mat0
        CMPLX(1.0,1.0), CMPLX(2.0,-1.0), CMPLX(3.0,1.0), CMPLX(4.0,-1.0),
        CMPLX(2.0,-1.0), CMPLX(3.0,1.0), CMPLX(4.0,-1.0), CMPLX(1.0,1.0),
        CMPLX(1.0,1.0), CMPLX(4.0,-1.0), CMPLX(3.0,1.0), CMPLX(2.0,-1.0),
        CMPLX(4.0,-1.0), CMPLX(3.0,1.0), CMPLX(2.0,-1.0), CMPLX(1.0,1.0)
    },
    { // mat1
        CMPLX(1.1,1.0), CMPLX(2.1,-1.0), CMPLX(3.1,1.0), CMPLX(4.1,-1.0),
        CMPLX(2.0,-1.0), CMPLX(3.0,1.0), CMPLX(4.0,-1.0), CMPLX(1.0,1.0),
        CMPLX(1.0,1.0), CMPLX(4.0,-1.0), CMPLX(3.0,1.0), CMPLX(2.0,-1.0),
        CMPLX(4.0,-1.0), CMPLX(3.0,1.0), CMPLX(2.0,-1.0), CMPLX(1.0,1.0)
    },
    { // matsum
        CMPLX(2.1,2.0), CMPLX(4.1,-2.0), CMPLX(6.1,2.0), CMPLX(8.1,-2.0),
        CMPLX(4.0,-2.0),CMPLX(6.0,2.0), CMPLX(8.0,-2.0), CMPLX(2.0,2.0),
        CMPLX(2.0,2.0), CMPLX(8.0,-2.0),CMPLX(6.0,2.0), CMPLX(4.0,-2.0),
        CMPLX(8.0,-2.0), CMPLX(6.0,2.0),CMPLX(4.0,-2.0),CMPLX(2.0,2.0)
    },
    { // matprod
        CMPLX(20.1,-5.9), CMPLX(36.1,2.1), CMPLX(24.1,-1.9), CMPLX(20.1, 6.1),
        CMPLX(20.2,5.9), CMPLX(28.2,-2.1), CMPLX(36.2,1.9), CMPLX(16.2,-6.1),
        CMPLX(16.1,-5.9), CMPLX(36.1,2.1), CMPLX(28.1,-1.9), CMPLX(20.1,6.1),
        CMPLX(20.4,5.9), CMPLX(24.4,-2.1), CMPLX(36.4,1.9), CMPLX(20.4,-6.1)
    },
    { // scale * mat0
        CMPLX(3.8,0.8), CMPLX(3.1,-5.3), CMPLX(8.4,-2.2), CMPLX(7.7,-8.3),
        CMPLX(3.1,-5.3),CMPLX(8.4,-2.2), CMPLX(7.7,-8.3), CMPLX(3.8,0.8),
        CMPLX(3.8,0.8), CMPLX(7.7,-8.3), CMPLX(8.4,-2.2), CMPLX(3.1,-5.3),
        CMPLX(7.7,-8.3),CMPLX(8.4,-2.2), CMPLX(3.1,-5.3), CMPLX(3.8,0.8)
    },
    { // scale0 * mat0 + scale1 * mat1
        CMPLX(-0.4,1.0), CMPLX(0.9,0.9), CMPLX(0.2,2.0), CMPLX(1.5,1.9),
        CMPLX(1.1,0.7), CMPLX(0.4,1.8), CMPLX(1.7,1.7), CMPLX(-0.2,0.8),
        CMPLX(-0.2,0.8), CMPLX(1.7,1.7), CMPLX(0.4,1.8), CMPLX(1.1,0.7),
        CMPLX(1.7,1.7), CMPLX(0.4,1.8), CMPLX(1.1,0.7), CMPLX(-0.2,0.8)
    },
    { // transpose mat0
        CMPLX(1.0,1.0), CMPLX(2.0,-1.0), CMPLX(1.0,1.0), CMPLX(4.0,-1.0),
        CMPLX(2.0,-1.0),CMPLX(3.0,1.0), CMPLX(4.0,-1.0), CMPLX(3.0,1.0),
        CMPLX(3.0,1.0), CMPLX(4.0,-1.0),CMPLX(3.0,1.0), CMPLX(2.0,-1.0),
        CMPLX(4.0,-1.0),CMPLX(1.0,1.0), CMPLX(2.0,-1.0),CMPLX(1.0,1.0)
    },
    { // inv mat0
        CMPLX(0.05,0.0), CMPLX(-0.2,0.1), CMPLX(-0.05,-0.1), CMPLX(0.3,0.0),
        CMPLX(-0.2,0.0), CMPLX(-0.05,-0.1), CMPLX(0.3,0.1), CMPLX(0.05,0.0),
        CMPLX(0.05,0.0), CMPLX(0.3,0.1), CMPLX(-0.05,-0.1), CMPLX(-0.2,0.0),
        CMPLX(0.3,0.0), CMPLX(-0.05,-0.1),CMPLX(-0.2,0.1), CMPLX(0.05,0.0)
    },
    SLC_c128_stdtol, CMPLX(2.3,-1.5), CMPLX(-2.0,2.0)
};
#pragma endregion basic_math_operation_test_data

#pragma region linear_equation_solver_test_data
r32_MiniLASolverUTParams_t r32_LAparams2 = {

};

r64_MiniLASolverUTParams_t r64_LAparams2 = {

};

c64_MiniLASolverUTParams_t c64_LAparams2 = {

};

c128_MiniLASolverUTParams_t c128_LAparams2 = {

};
#pragma endregion linear_equation_solver_test_data

SLC_errno_t SLC_MiniLAUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_TestArgs_t r32_args = { 0, &r32_LAparams };
        SLC_TestArgs_t r64_args = { 0, &r64_LAparams };
        SLC_TestArgs_t c64_args = { 0, &c64_LAparams };
        SLC_TestArgs_t c128_args = { 0, &c128_LAparams };
        SLC_test2(err, SLC_r32_MiniLAUT, &r32_args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_MiniLAUT, &r64_args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_MiniLAUT, &c64_args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_MiniLAUT, &c128_args, __func__, __LINE__);

        r32_args.data = &r32_LAparams2;
        r64_args.data = &r64_LAparams2;
        c64_args.data = &c64_LAparams2;
        c128_args.data = &c128_LAparams2;
        SLC_test2(err, SLC_r32_MiniLASolverUT, &r32_args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_MiniLASolverUT, &r64_args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_MiniLASolverUT, &c64_args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_MiniLASolverUT, &c128_args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
