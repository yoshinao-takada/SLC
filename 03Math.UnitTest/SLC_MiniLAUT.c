#include "SLC/SLC_MiniLA.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_Numbers.h"
#include <assert.h>

#pragma region Unit_tests_for_MiniLA_with_base_number_type_SLC_r32_t
#pragma region basic_matrix_operations
typedef struct {
    SLC_r32_t mat0[16], mat1[16];
    SLC_r32_t matsum[16], matprod[16];
    SLC_r32_t mattranspose[16], matinv[16];
} r32_MiniLAUTParams_t, *r32_PMiniLAUTParams_t;
typedef const r32_MiniLAUTParams_t *r32_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matr32_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr32_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r32_PCMiniLAUTParams_t params = (r32_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
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
    SLC_r64_t mat0[16], mat1[16];
    SLC_r64_t matsum[16], matprod[16];
    SLC_r64_t mattranspose[16], matinv[16];
} r64_MiniLAUTParams_t, *r64_PMiniLAUTParams_t;
typedef const r64_MiniLAUTParams_t *r64_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matr64_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matr64_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    r64_PCMiniLAUTParams_t params = (r64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
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
    SLC_c64_t mat0[16], mat1[16];
    SLC_c64_t matsum[16], matprod[16];
    SLC_c64_t mattranspose[16], matinv[16];
} c64_MiniLAUTParams_t, *c64_PMiniLAUTParams_t;
typedef const c64_MiniLAUTParams_t *c64_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matc64_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc64_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c64_PCMiniLAUTParams_t params = (c64_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
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
    SLC_c128_t mat0[16], mat1[16];
    SLC_c128_t matsum[16], matprod[16];
    SLC_c128_t mattranspose[16], matinv[16];
} c128_MiniLAUTParams_t, *c128_PMiniLAUTParams_t;
typedef const c128_MiniLAUTParams_t *c128_PCMiniLAUTParams_t;

SLC_errno_t SLC_Matc128_AddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_Matc128_ScaleAddUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    c128_PCMiniLAUTParams_t params = (c128_PCMiniLAUTParams_t)(args->data);
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
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
r32_MiniLAUTParams_t r32_LAparams = {

};

r64_MiniLAUTParams_t r64_LAparams = {

};

c64_MiniLAUTParams_t c64_LAparams = {

};

c128_MiniLAUTParams_t c128_LAparams = {

};

r32_MiniLASolverUTParams_t r32_LAparams2 = {

};

r64_MiniLASolverUTParams_t r64_LAparams2 = {

};

c64_MiniLASolverUTParams_t c64_LAparams2 = {

};

c128_MiniLASolverUTParams_t c128_LAparams2 = {

};

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
