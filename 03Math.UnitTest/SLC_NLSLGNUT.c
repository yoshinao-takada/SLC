#include "SLC/SLC_NLSLGN.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_NumbersCopy.h"
#include "SLC/SLC_MiniBLAS.h"
#include "SLC/SLC_MiniLA.h"
#include <assert.h>
#include <alloca.h>

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
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[0]*x[0]+x[1]*x[2] - c[0];
        y[1] = x[0]*x[1] + x[1]*x[3] - c[1];
        y[2] = x[2]*x[0] + x[3]*x[2] - c[2];
        y[3] = x[2]*x[1] + x[3]*x[3] - c[3];
        y[4] = x[0] + x[3] - c[4];
    } while (0);
    return err;
}


SLC_errno_t J0r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = ((SLC_r32_t)2)*x[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = SLC_r32_units[0];
        y[4] = SLC_r32_units[1];
    } while (0);
    return err;
}

SLC_errno_t J1r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[2];
        y[1] = x[0] + x[3];
        y[4] = y[2] = SLC_r32_units[0];
        y[3] = x[2];
    } while (0);
    return err;
}

SLC_errno_t J2r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[1];
        y[4] = y[1] = SLC_r32_units[0];
        y[2] = x[0] + x[3];
        y[3] = x[1];
    } while (0);
    return err;
}

SLC_errno_t J3r32(
    SLC_r32_t* y, SLC_size_t cy,
    const SLC_r32_t* x, SLC_size_t cx,
    const SLC_r32_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = SLC_r32_units[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = ((SLC_r32_t)2)*x[3];
        y[4] = SLC_r32_units[1];
    } while (0);
    return err;
}

// fill x with random numbers
void FillXr32(SLC_r32_t* x, SLC_size_t cx)
{
    for (SLC_size_t i = 0; i < cx; i++)
    {
        x[i] = SLC_r32_rand;
    }
}

SLC_errno_t SLC_NLSLGNUTr32_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_r32_t params = (PCNLSLGNUT_r32_t)args->data;
    SLC_PNLSLGNSolverr32_t solver = NULL;
    SLC_r32_t *x = alloca(sizeof(SLC_r32_t) * (params->cx + params->cy + params->cc));
    SLC_r32_t *y = x + params->cx;
    SLC_r32_t *c = y + params->cy;
    do {
        // create x, y, c vectors
        SLC_Array_t mat0 = {{sizeof(SLC_r32_t), 2, 2, 1 }, { params->mat0}};
        SLC_Array_t mat0_x_mat0 = { { sizeof(SLC_r32_t), 2, 2, 1 }, { c } };
        SLC_Array_t matwork = { { sizeof(SLC_r32_t), 2, 2, 1 }, { y } };
        SLC_Matr32_Mul(&mat0_x_mat0, &mat0, &mat0, &matwork);
        solver = SLC_NLSLGNSolverr32_New(params->cx, params->cy, params->cc);
        c[4] = params->mat0[0] + params->mat0[3];
        FillXr32(x, params->cx);
        SLC_PNLSLGNConfr32_t conf = SLC_NLSLGNSolverr32_Conf(solver);
        conf->jacobian[0] = J0r32;
        conf->jacobian[1] = J1r32;
        conf->jacobian[2] = J2r32;
        conf->jacobian[3] = J3r32;
        conf->base.objective = Objectiver32;
        conf->base.c = c;
        conf->base.xInitial = x;
        conf->base.maxIter = 50;
        SLC_NLSLGNSolverr32_Init(solver);
        SLC_NLSLGNSolverr32_Execute(solver);
        const SLC_r32_t* xSolved = SLC_NLSLGNSolverr32_X(solver);
        for (SLC_size_t i = 0; i < params->cx; i++)
        {
            if (!SLC_r32_areequal(params->mat0[i], xSolved[i], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_NLSLGNSolverr32_Delete(&solver);
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
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[0]*x[0]+x[1]*x[2] - c[0];
        y[1] = x[0]*x[1] + x[1]*x[3] - c[1];
        y[2] = x[2]*x[0] + x[3]*x[2] - c[2];
        y[3] = x[2]*x[1] + x[3]*x[3] - c[3];
        y[4] = x[0] + x[3] - c[4];
    } while (0);
    return err;
}


SLC_errno_t J0r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = ((SLC_r64_t)2)*x[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = SLC_r64_units[0];
        y[4] = SLC_r64_units[1];
    } while (0);
    return err;
}

SLC_errno_t J1r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[2];
        y[1] = x[0] + x[3];
        y[4] = y[2] = SLC_r64_units[0];
        y[3] = x[2];
    } while (0);
    return err;
}

SLC_errno_t J2r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[1];
        y[4] = y[1] = SLC_r64_units[0];
        y[2] = x[0] + x[3];
        y[3] = x[1];
    } while (0);
    return err;
}

SLC_errno_t J3r64(
    SLC_r64_t* y, SLC_size_t cy,
    const SLC_r64_t* x, SLC_size_t cx,
    const SLC_r64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = SLC_r64_units[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = ((SLC_r64_t)2)*x[3];
        y[4] = SLC_r64_units[1];
    } while (0);
    return err;
}

// fill x with random numbers
void FillXr64(SLC_r64_t* x, SLC_size_t cx)
{
    for (SLC_size_t i = 0; i < cx; i++)
    {
        x[i] = SLC_r64_rand;
    }
}

SLC_errno_t SLC_NLSLGNUTr64_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_r64_t params = (PCNLSLGNUT_r64_t)args->data;
    SLC_PNLSLGNSolverr64_t solver = NULL;
    SLC_r64_t *x = alloca(sizeof(SLC_r64_t) * (params->cx + params->cy + params->cc));
    SLC_r64_t *y = x + params->cx;
    SLC_r64_t *c = y + params->cy;
    do {
        // create x, y, c vectors
        SLC_Array_t mat0 = {{sizeof(SLC_r64_t), 2, 2, 1 }, { params->mat0}};
        SLC_Array_t mat0_x_mat0 = { { sizeof(SLC_r64_t), 2, 2, 1 }, { c } };
        SLC_Array_t matwork = { { sizeof(SLC_r64_t), 2, 2, 1 }, { y } };
        SLC_Matr64_Mul(&mat0_x_mat0, &mat0, &mat0, &matwork);
        solver = SLC_NLSLGNSolverr64_New(params->cx, params->cy, params->cc);
        c[4] = params->mat0[0] + params->mat0[3];
        FillXr64(x, params->cx);
        SLC_PNLSLGNConfr64_t conf = SLC_NLSLGNSolverr64_Conf(solver);
        conf->jacobian[0] = J0r64;
        conf->jacobian[1] = J1r64;
        conf->jacobian[2] = J2r64;
        conf->jacobian[3] = J3r64;
        conf->base.objective = Objectiver64;
        conf->base.c = c;
        conf->base.xInitial = x;
        conf->base.maxIter = 50;
        SLC_NLSLGNSolverr64_Init(solver);
        SLC_NLSLGNSolverr64_Execute(solver);
        const SLC_r64_t* xSolved = SLC_NLSLGNSolverr64_X(solver);
        for (SLC_size_t i = 0; i < params->cx; i++)
        {
            if (!SLC_r64_areequal(params->mat0[i], xSolved[i], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_NLSLGNSolverr64_Delete(&solver);
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
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[0]*x[0]+x[1]*x[2] - c[0];
        y[1] = x[0]*x[1] + x[1]*x[3] - c[1];
        y[2] = x[2]*x[0] + x[3]*x[2] - c[2];
        y[3] = x[2]*x[1] + x[3]*x[3] - c[3];
        y[4] = x[0] + x[3] - c[4];
    } while (0);
    return err;
}


SLC_errno_t J0c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = ((SLC_c64_t)2)*x[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = SLC_c64_units[0];
        y[4] = SLC_c64_units[1];
    } while (0);
    return err;
}

SLC_errno_t J1c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[2];
        y[1] = x[0] + x[3];
        y[4] = y[2] = SLC_c64_units[0];
        y[3] = x[2];
    } while (0);
    return err;
}

SLC_errno_t J2c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[1];
        y[4] = y[1] = SLC_c64_units[0];
        y[2] = x[0] + x[3];
        y[3] = x[1];
    } while (0);
    return err;
}

SLC_errno_t J3c64(
    SLC_c64_t* y, SLC_size_t cy,
    const SLC_c64_t* x, SLC_size_t cx,
    const SLC_c64_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = SLC_c64_units[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = ((SLC_c64_t)2)*x[3];
        y[4] = SLC_c64_units[1];
    } while (0);
    return err;
}

// fill x with random numbers
void FillXc64(SLC_c64_t* x, SLC_size_t cx)
{
    for (SLC_size_t i = 0; i < cx; i++)
    {
        x[i] = SLC_c64_rand;
    }
}

SLC_errno_t SLC_NLSLGNUTc64_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_c64_t params = (PCNLSLGNUT_c64_t)args->data;
    SLC_PNLSLGNSolverc64_t solver = NULL;
    SLC_c64_t *x = alloca(sizeof(SLC_c64_t) * (params->cx + params->cy + params->cc));
    SLC_c64_t *y = x + params->cx;
    SLC_c64_t *c = y + params->cy;
    do {
        // create x, y, c vectors
        SLC_Array_t mat0 = {{sizeof(SLC_c64_t), 2, 2, 1 }, { params->mat0}};
        SLC_Array_t mat0_x_mat0 = { { sizeof(SLC_c64_t), 2, 2, 1 }, { c } };
        SLC_Array_t matwork = { { sizeof(SLC_c64_t), 2, 2, 1 }, { y } };
        SLC_Matc64_Mul(&mat0_x_mat0, &mat0, &mat0, &matwork);
        solver = SLC_NLSLGNSolverc64_New(params->cx, params->cy, params->cc);
        c[4] = params->mat0[0] + params->mat0[3];
        FillXc64(x, params->cx);
        SLC_PNLSLGNConfc64_t conf = SLC_NLSLGNSolverc64_Conf(solver);
        conf->jacobian[0] = J0c64;
        conf->jacobian[1] = J1c64;
        conf->jacobian[2] = J2c64;
        conf->jacobian[3] = J3c64;
        conf->base.objective = Objectivec64;
        conf->base.c = c;
        conf->base.xInitial = x;
        conf->base.maxIter = 50;
        SLC_NLSLGNSolverc64_Init(solver);
        SLC_NLSLGNSolverc64_Execute(solver);
        const SLC_c64_t* xSolved = SLC_NLSLGNSolverc64_X(solver);
        for (SLC_size_t i = 0; i < params->cx; i++)
        {
            if (!SLC_c64_areequal(params->mat0[i], xSolved[i], SLC_c64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_NLSLGNSolverc64_Delete(&solver);
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
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[0]*x[0]+x[1]*x[2] - c[0];
        y[1] = x[0]*x[1] + x[1]*x[3] - c[1];
        y[2] = x[2]*x[0] + x[3]*x[2] - c[2];
        y[3] = x[2]*x[1] + x[3]*x[3] - c[3];
        y[4] = x[0] + x[3] - c[4];
    } while (0);
    return err;
}


SLC_errno_t J0c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = ((SLC_c128_t)2)*x[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = SLC_c128_units[0];
        y[4] = SLC_c128_units[1];
    } while (0);
    return err;
}

SLC_errno_t J1c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[2];
        y[1] = x[0] + x[3];
        y[4] = y[2] = SLC_c128_units[0];
        y[3] = x[2];
    } while (0);
    return err;
}

SLC_errno_t J2c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = x[1];
        y[4] = y[1] = SLC_c128_units[0];
        y[2] = x[0] + x[3];
        y[3] = x[1];
    } while (0);
    return err;
}

SLC_errno_t J3c128(
    SLC_c128_t* y, SLC_size_t cy,
    const SLC_c128_t* x, SLC_size_t cx,
    const SLC_c128_t* c, SLC_size_t cc
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert(cx == 4);
    assert(cy == 5);
    assert(cc == 5);
    do {
        y[0] = SLC_c128_units[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = ((SLC_c128_t)2)*x[3];
        y[4] = SLC_c128_units[1];
    } while (0);
    return err;
}

// fill x with random numbers
void FillXc128(SLC_c128_t* x, SLC_size_t cx)
{
    for (SLC_size_t i = 0; i < cx; i++)
    {
        x[i] = SLC_c128_rand;
    }
}

SLC_errno_t SLC_NLSLGNUTc128_Square_and_Trace(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    PCNLSLGNUT_c128_t params = (PCNLSLGNUT_c128_t)args->data;
    SLC_PNLSLGNSolverc128_t solver = NULL;
    SLC_c128_t *x = alloca(sizeof(SLC_c128_t) * (params->cx + params->cy + params->cc));
    SLC_c128_t *y = x + params->cx;
    SLC_c128_t *c = y + params->cy;
    do {
        // create x, y, c vectors
        SLC_Array_t mat0 = {{sizeof(SLC_c128_t), 2, 2, 1 }, { params->mat0}};
        SLC_Array_t mat0_x_mat0 = { { sizeof(SLC_c128_t), 2, 2, 1 }, { c } };
        SLC_Array_t matwork = { { sizeof(SLC_c128_t), 2, 2, 1 }, { y } };
        SLC_Matc128_Mul(&mat0_x_mat0, &mat0, &mat0, &matwork);
        solver = SLC_NLSLGNSolverc128_New(params->cx, params->cy, params->cc);
        c[4] = params->mat0[0] + params->mat0[3];
        FillXc128(x, params->cx);
        SLC_PNLSLGNConfc128_t conf = SLC_NLSLGNSolverc128_Conf(solver);
        conf->jacobian[0] = J0c128;
        conf->jacobian[1] = J1c128;
        conf->jacobian[2] = J2c128;
        conf->jacobian[3] = J3c128;
        conf->base.objective = Objectivec128;
        conf->base.c = c;
        conf->base.xInitial = x;
        conf->base.maxIter = 50;
        SLC_NLSLGNSolverc128_Init(solver);
        SLC_NLSLGNSolverc128_Execute(solver);
        const SLC_c128_t* xSolved = SLC_NLSLGNSolverc128_X(solver);
        for (SLC_size_t i = 0; i < params->cx; i++)
        {
            if (!SLC_c128_areequal(params->mat0[i], xSolved[i], SLC_c128_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s, %d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_NLSLGNSolverc128_Delete(&solver);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion UnitTest_for_Gauss-Newton_Nonlinear_solvers_with_base_number_type_c128


static const NLSLGNUT_r32_t TestData_r32_Square_and_Trace =
{
    { 1.0f, 2.3f, -1.5f, -2.5f }, // mat0
    { -2.45f, -3.45f, 2.25f, 2.8f }, // mat0_2
    -1.5f, // trace(mat0)
    4, 5, 5, // cx, cy, cz
    Objectiver32, // objective
    { J0r32, J1r32, J2r32, J3r32 }
};

static const NLSLGNUT_r64_t TestData_r64_Square_and_Trace =
{
    { 1.0f, 2.3f, -1.5f, -2.5f }, // mat0
    { -2.45f, -3.45f, 2.25f, 2.8f }, // mat0_2
    -1.5f, // trace(mat0)
    4, 5, 5, // cx, cy, cz
    Objectiver64, // objective
    { J0r64, J1r64, J2r64, J3r64 }
};

static const NLSLGNUT_c64_t TestData_c64_Square_and_Trace = 
{
    { CMPLXF(1.0f, 2.3f), CMPLXF(-1.5f, -2.5f), CMPLXF(-2.5f, 1.0f), CMPLXF(2.3f, -1.5f) },
    { CMPLXF(1.96f, 9.35f), CMPLXF(-2.95f, -9.45f), CMPLXF(-9.05f, 1.3f), CMPLXF(9.29f, -2.15f) },
    CMPLXF(3.3f, 0.8f), // trace(mat0)
    4, 5, 5, // cx, cy, cz
    Objectivec64, // objective
    { J0c64, J1c64, J2c64, J3c64 }
};

static const NLSLGNUT_c128_t TestData_c128_Square_and_Trace = 
{
    { CMPLX(1.0, 2.3), CMPLX(-1.5, -2.5), CMPLX(-2.5, 1.0), CMPLX(2.3, -1.5) },
    { CMPLX(1.96, 9.35), CMPLX(-2.95, -9.45), CMPLX(-9.05, 1.3), CMPLX(9.29, -2.15) },
    CMPLX(3.3, 0.8), // trace(mat0)
    4, 5, 5, // cx, cy, cz
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
        SLC_test2(err, SLC_NLSLGNUTr32_Square_and_Trace, &args_r32, __func__, __LINE__);
        SLC_test2(err, SLC_NLSLGNUTr64_Square_and_Trace, &args_r64, __func__, __LINE__);
        SLC_test2(err, SLC_NLSLGNUTc64_Square_and_Trace, &args_c64, __func__, __LINE__);
        SLC_test2(err, SLC_NLSLGNUTc128_Square_and_Trace, &args_c128, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
