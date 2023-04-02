#include "SLC/SLC_NLSLGN.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_NumbersCopy.h"
#include "SLC/SLC_MiniBLAS.h"
#include "SLC/SLC_MiniLA.h"
#include <assert.h>

#pragma region UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_r32
typedef struct {
    SLC_r32_t mat0[4], mat0_2[4];
    SLC_r32_t trace_mat0;
    SLC_size_t cx, cy, cc;
    SLC_GVVF_r32 objective;
    SLC_GVVF_r32 jacobian[4];
} NLSLGNUT_r32_t, *PNLSLGNUT_r32_t;
typedef const NLSLGNUT_r32_t *PCNLSLGNUT_r32_t;

SLC_errno_t Objectiver32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}


SLC_errno_t J0r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J1r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J2r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J3r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t SLC_NLSLGNUTr32_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_r32_t params = (PCNLSLGNUT_r32_t)args->data;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_r32

#pragma region UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_r64
typedef struct {
    SLC_r64_t mat0[4], mat0_2[4];
    SLC_r64_t trace_mat0;
    SLC_size_t cx, cy, cc;
    SLC_GVVF_r64 objective;
    SLC_GVVF_r64 jacobian[4];
} NLSLGNUT_r64_t, *PNLSLGNUT_r64_t;
typedef const NLSLGNUT_r64_t *PCNLSLGNUT_r64_t;

SLC_errno_t Objectiver64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}


SLC_errno_t J0r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J1r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J2r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J3r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t SLC_NLSLGNUTr64_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_r64_t params = (PCNLSLGNUT_r64_t)args->data;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_r64

#pragma region UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_c64
typedef struct {
    SLC_c64_t mat0[4], mat0_2[4];
    SLC_c64_t trace_mat0;
    SLC_size_t cx, cy, cc;
    SLC_GVVF_c64 objective;
    SLC_GVVF_c64 jacobian[4];
} NLSLGNUT_c64_t, *PNLSLGNUT_c64_t;
typedef const NLSLGNUT_c64_t *PCNLSLGNUT_c64_t;

SLC_errno_t Objectivec64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}


SLC_errno_t J0c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J1c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J2c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J3c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t SLC_NLSLGNUTc64_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_c64_t params = (PCNLSLGNUT_c64_t)args->data;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_c64

#pragma region UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_c128
typedef struct {
    SLC_c128_t mat0[4], mat0_2[4];
    SLC_c128_t trace_mat0;
    SLC_size_t cx, cy, cc;
    SLC_GVVF_c128 objective;
    SLC_GVVF_c128 jacobian[4];
} NLSLGNUT_c128_t, *PNLSLGNUT_c128_t;
typedef const NLSLGNUT_c128_t *PCNLSLGNUT_c128_t;

SLC_errno_t Objectivec128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}


SLC_errno_t J0c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J1c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J2c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t J3c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    return EXIT_SUCCESS;
}

SLC_errno_t SLC_NLSLGNUTc128_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_c128_t params = (PCNLSLGNUT_c128_t)args->data;
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_c128


static const NLSLGNUT_r32_t TestData_r32_Square_and_Trace =
{
    { 1.0f, 2.3f, -1.5f, -2.5f }, // mat0
    { -2.45f, -3.45f, 2.25f, 2.8f }, // mat0_2
    -1.5f, // trace
    4, 6, 0,
    Objectiver32, // objective
    { J0r32, J1r32, J2r32, J3r32 }
};

static const NLSLGNUT_r64_t TestData_r64_Square_and_Trace =
{
    { 1.0f, 2.3f, -1.5f, -2.5f }, // mat0
    { -2.45f, -3.45f, 2.25f, 2.8f }, // mat0_2
    -1.5f, // trace
    4, 6, 0,
    Objectiver64, // objective
    { J0r64, J1r64, J2r64, J3r64 }
};

static const NLSLGNUT_c64_t TestData_c64_Square_and_Trace = 
{
    { CMPLXF(1.0f, 2.3f), CMPLXF(-1.5f, -2.5f), CMPLXF(-2.5f, 1.0f), CMPLXF(2.3f, -1.5f) },
    { CMPLXF(1.96f, 9.35f), CMPLXF(-2.95f, -9.45f), CMPLXF(-9.05f, 1.3f), CMPLXF(9.29f, -2.15f) },
    CMPLXF(3.3f, 0.8f),
    4, 6, 0,
    Objectivec64, // objective
    { J0c64, J1c64, J2c64, J3c64 }
};

static const NLSLGNUT_c128_t TestData_c128_Square_and_Trace = 
{
    { CMPLX(1.0, 2.3), CMPLX(-1.5, -2.5), CMPLX(-2.5, 1.0), CMPLX(2.3, -1.5) },
    { CMPLX(1.96, 9.35), CMPLX(-2.95, -9.45), CMPLX(-9.05, 1.3), CMPLX(9.29, -2.15) },
    CMPLX(3.3, 0.8),
    4, 6, 0,
    Objectivec128, // objective
    { J0c128, J1c128, J2c128, J3c128 }
};

SLC_errno_t SLC_NLSLGNUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_TestArgs_t args_r32 = { settings, &TestData_r32_Square_and_Trace };
    SLC_TestArgs_t args_r64 = { settings, &TestData_r64_Square_and_Trace };
    SLC_TestArgs_t args_c64 = { settings, &TestData_c64_Square_and_Trace };
    SLC_TestArgs_t args_c128 = { settings, &TestData_c128_Square_and_Trace };
    do {

    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
