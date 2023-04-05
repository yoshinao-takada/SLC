#include "SLC/SLC_NLSLGN.h"
#include "SLC/SLC_Array.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_NumbersCopy.h"
#include "SLC/SLC_MiniBLAS.h"
#include "SLC/SLC_MiniLA.h"
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#pragma region SLC_NLSLGNSolverr32_implimentation
typedef void (*NLSLGNSolverTracer32)(SLC_PNLSLGNSolverr32_t solver);

struct SLC_NLSLGNSolverr32 {
    // configuration parameters
    SLC_NLSLGNConfr32_t conf;

    // working matrices
    SLC_PArray_t 
        _xcv_new, // renewed _xcv
        _xcv, // X column vector
        _delta_xcv, // 
        _xcv_workT, // transposed _xcv size matrix for work area
        _ycv, // Y column vector
        _jcolbuf, // Jacobian column buffer
        _j, _jtc; // Jacobian and its tranpose conjugate
    SLC_PArray_t _jtworkT, _jtcworkT, _ycvworkT; // transposed work area for matrix multiplication
    SLC_PArray_t _jtc_j; // product of transconj Jacobian and the Jacobian.
    SLC_PArray_t  _inv_jtc_j; // and its inverse.
    SLC_PArray_t _jtc_y; // prouct of transconj Jacobian and _y.
    SLC_PArray_t _invwork; // work matrix for inverting matrices
    
    // convergence cliterion
    SLC_r32_t _normDeltaX, _normY;

    // operating state
    SLC_NLSLState_t state;
    SLC_size_t iter;
    NLSLGNSolverTracer32 traceIXY, traceIJ, traceINormDXNormY;
};

#define SAFEFREE(__var) if (__var) { free(__var); __var = NULL; }
void FreeAllArraysr32(SLC_PNLSLGNSolverr32_t solver)
{
    SAFEFREE(solver->_xcv);
    SAFEFREE(solver->_xcv_new);
    SAFEFREE(solver->_delta_xcv);
    SAFEFREE(solver->_xcv_workT);
    SAFEFREE(solver->_ycv);
    SAFEFREE(solver->_jcolbuf);
    SAFEFREE(solver->_j);
    SAFEFREE(solver->_jtc);
    SAFEFREE(solver->_jtworkT);
    SAFEFREE(solver->_jtcworkT);
    SAFEFREE(solver->_ycvworkT);
    SAFEFREE(solver->_jtc_j);
    SAFEFREE(solver->_inv_jtc_j);
    SAFEFREE(solver->_jtc_y);
    SAFEFREE(solver->_invwork);
}
#undef SAFEFREE
#pragma region Trace_methods_are_private_to_this_source_code 
static void NLSLGNSolverTracer32_None(SLC_PNLSLGNSolverr32_t solver)
{
    // does nothing
}

static void NLSLGNSolverTracer32_IXY(SLC_PNLSLGNSolverr32_t solver)
{
    SLC_PArray_t x = solver->_xcv;
    SLC_PArray_t y = solver->_ycv;
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    fprintf(trace_out, "x={");
    for (SLC_i16_t i = 0; i < x->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_r32_print(trace_out, delimiter, x->data._r32[i]);
    }
    fprintf(trace_out, "}\ny={");
    for (SLC_i16_t i = 0; i < y->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_r32_print(trace_out, delimiter, y->data._r32[i]);
    }
    fprintf(trace_out, "}\n");
}

static void NLSLGNSolverTracer32_IJ(SLC_PNLSLGNSolverr32_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_Matr32_Print(trace_out, "Jacobian: ", solver->_j, "");
}

static void NLSLGNSolverTracer32_INormDXNormY(SLC_PNLSLGNSolverr32_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_r32_print(trace_out, "norm(delta-x) = ", solver->_normDeltaX);
    SLC_r32_print(trace_out, "\tnorm(y) = ", solver->_normY);
    fprintf(trace_out, "\n");
}
#pragma endregion Trace_methods_are_private_to_this_source_code 

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverr32_t SLC_NLSLGNSolverr32_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PNLSLGNSolverr32_t p = NULL;
    do {
        SLC_size_t alloc_size_core = SLC_ALIGN8(sizeof(SLC_NLSLGNSolverr32_t));
        SLC_size_t alloc_size_jacobian = SLC_ALIGN8(sizeof(SLC_GVVF_r32) * cx);
        SLC_size_t alloc_size = alloc_size_core + alloc_size_jacobian;
        p = (SLC_PNLSLGNSolverr32_t)aligned_alloc(8, alloc_size);
        SLC_IfNullERR(p, err, __FILE__, __func__, __LINE__);
        p->conf.base.trace.trace_out = stdout;
        p->conf.base.trace.item = NLSLTraceItem_None;
        p->conf.base.cx = cx;
        p->conf.base.cy = cy;
        p->conf.base.cc = cc;
        p->conf.base.maxIter = 100;
        p->conf.base.c = p->conf.base.xInitial = NULL;
        p->conf.base.dxNormMax = cx * SLC_r32_stdtol;
        p->conf.base.yNormMax = cy * (SLC_r32_stdtol * (SLC_r32_t)1000);
        p->conf.base.objective = NULL;
        p->conf.jacobian = (SLC_GVVF_r32*)((SLC_u8_t*)p + alloc_size_core);
        p->state = NLSLState_created;
        p->iter = 0;
        p->traceINormDXNormY = p->traceIJ = p->traceIXY = NLSLGNSolverTracer32_None;
    } while (0);
    return p;
}

// delete an existing instance
void SLC_NLSLGNSolverr32_Delete(SLC_PNLSLGNSolverr32_t *ppsolver)
{
    assert(ppsolver && *ppsolver);
    SLC_PNLSLGNSolverr32_t p = *ppsolver;
    FreeAllArraysr32(p);
    free(p);
    *ppsolver = NULL;
}

// retrieve a configuration struct
SLC_PNLSLGNConfr32_t SLC_NLSLGNSolverr32_Conf(SLC_PNLSLGNSolverr32_t solver)
{
    return &solver->conf;
}

static void NLSLGNSolverr32_InitTrace(SLC_PNLSLGNSolverr32_t solver)
{
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IXY))
    {
        solver->traceIXY = NLSLGNSolverTracer32_IXY;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IJ))
    {
        solver->traceIJ = NLSLGNSolverTracer32_IJ;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_INormDXNormY))
    {
        solver->traceINormDXNormY = NLSLGNSolverTracer32_INormDXNormY;
    }
}

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverr32_Init(SLC_PNLSLGNSolverr32_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_i16_t unit_size = sizeof(SLC_r32_t);
    assert(solver->conf.base.objective);
    assert(solver->conf.base.cc > 0 && solver->conf.base.c); // const parameters has been initialized.
    for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
    {
        assert(solver->conf.jacobian[i]);
    }
    do {
        { // init _xcv, _xcv_new, _ycv, _ycvworkT
            SLC_4i16_t xcv_size = { unit_size, 1, solver->conf.base.cx, 1 };
            SLC_4i16_t transposed_xcv_size = SLC_TransposedMatSize(xcv_size);
            SLC_4i16_t ycv_size = { unit_size, 1, solver->conf.base.cy, 1 };
            SLC_4i16_t transposed_ycv_size = SLC_TransposedMatSize(ycv_size);
            SLC_IfNullERR(solver->_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_delta_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_new = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_workT = SLC_Array_Alloc(transposed_xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycv = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jcolbuf = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycvworkT = SLC_Array_Alloc(transposed_ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc_y = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
        } { // init _j, _jtc, _jtworkT, _jtcworkT
            SLC_4i16_t jsize = { unit_size, solver->conf.base.cx, solver->conf.base.cy, 1 };
            SLC_4i16_t jtcsize = SLC_TransposedMatSize(jsize);
            SLC_IfNullERR(solver->_j = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtworkT = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtcworkT = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
        } { // init _jtc_j, _inv_jtc_j, _invwork
            SLC_4i16_t jtc_j_size = { unit_size, solver->conf.base.cx, solver->conf.base.cx, 1 };
            SLC_4i16_t invwork_size = SLC_InvMatWorkSize(jtc_j_size);
            SLC_IfNullERR(solver->_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_inv_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_invwork = SLC_Array_Alloc(invwork_size), err, __FILE__, __func__, __LINE__);
        }
        SLC_r32_copy(solver->_xcv->data._r32, 1, solver->conf.base.xInitial, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._r32, solver->conf.base.cy,
            solver->_xcv->data._r32, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        solver->state = (err) ? NLSLState_errabort : NLSLState_initialized;
        solver->iter = 0;
        NLSLGNSolverr32_InitTrace(solver);
    } while (0);
    if (err) FreeAllArraysr32(solver);
    return err;
}

// calculate new X vector
SLC_errno_t RenewXr32(SLC_PNLSLGNSolverr32_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_size_t jacobian_columns = solver->conf.base.cx;
        SLC_size_t jacobian_rows = solver->conf.base.cy;
        for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
        {
            err = solver->conf.jacobian[i](
                solver->_jcolbuf->data._r32, solver->conf.base.cy,
                solver->_xcv->data._r32, solver->conf.base.cx,
                solver->conf.base.c, solver->conf.base.cc
            );
            if (err)
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            SLC_r32_copy(solver->_j->data._r32 + i, jacobian_columns,
                solver->_jcolbuf->data._r32, 1, jacobian_rows);
        }
        if (err) break;
        SLC_Matr32_TransConj(solver->_jtc, solver->_j);
        SLC_Matr32_Mul(solver->_jtc_j, solver->_jtc, solver->_j, solver->_jtworkT);
        SLC_Matr32_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        err = SLC_Matr32_Inv(solver->_inv_jtc_j, solver->_jtc_j, solver->_invwork);
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            break;
        }
        SLC_Matr32_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        SLC_Matr32_Mul(solver->_delta_xcv, solver->_inv_jtc_j, solver->_jtc_y, solver->_xcv_workT);
        SLC_Matr32_ScaleAdd(solver->_xcv_new, solver->_xcv, &SLC_r32_units[1], 
            solver->_delta_xcv, &SLC_r32_units[2]);
        SLC_r32_copy(solver->_xcv->data._r32, 1, solver->_xcv_new->data._r32, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._r32, solver->conf.base.cy,
            solver->_xcv->data._r32, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            solver->state = NLSLState_errabort;
            break;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_NLSLGNSolverr32_Execute(SLC_PNLSLGNSolverr32_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        solver->state = NLSLState_running;
        for (; solver->iter < solver->conf.base.maxIter; solver->iter++)
        {
            solver->traceIXY(solver); // debug trace
            // calculating a new X vector to update solver->_xcv_new.
            if (EXIT_SUCCESS != (err = RenewXr32(solver)))
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            solver->traceIJ(solver); // debug trace
            // check delta-x convergence
            solver->_normDeltaX = SLC_r32_abssum(solver->_delta_xcv->data._r32, solver->conf.base.cx);
            solver->_normY = SLC_r32_abssum(solver->_ycv->data._r32, solver->conf.base.cy);
            solver->traceINormDXNormY(solver); // debug trace
            if ((solver->_normDeltaX < solver->conf.base.dxNormMax) && (solver->_normY < solver->conf.base.yNormMax))
            {
                solver->state = NLSLState_converged;
                break;
            }
        }
        if (solver->iter == solver->conf.base.maxIter)
        {
            err = SLC_ENOCONV;
            solver->state = NLSLState_iterlimit;
        }
    } while (0);
    return err;
}

// retrieve x and y vector
const SLC_r32_t* SLC_NLSLGNSolverr32_X(SLC_PNLSLGNSolverr32_t solver) { return solver->_xcv->data._r32; }
const SLC_r32_t* SLC_NLSLGNSolverr32_Y(SLC_PNLSLGNSolverr32_t solver) { return solver->_ycv->data._r32; }

// retrieve L1 norm of dx and y vector
SLC_r32_t SLC_NLSLGNSolverr32_L1NormDX(SLC_PNLSLGNSolverr32_t solver) { return solver->_normDeltaX; }
SLC_r32_t SLC_NLSLGNSolverr32_L1NormY(SLC_PNLSLGNSolverr32_t solver) { return solver->_normY; }

#pragma endregion SLC_NLSLGNSolverr32_implimentation

#pragma region SLC_NLSLGNSolverr64_implimentation
typedef void (*NLSLGNSolverTracer64)(SLC_PNLSLGNSolverr64_t solver);

struct SLC_NLSLGNSolverr64 {
    // configuration parameters
    SLC_NLSLGNConfr64_t conf;

    // working matrices
    SLC_PArray_t 
        _xcv_new, // renewed _xcv
        _xcv, // X column vector
        _delta_xcv, // 
        _xcv_workT, // transposed _xcv size matrix for work area
        _ycv, // Y column vector
        _jcolbuf, // Jacobian column buffer
        _j, _jtc; // Jacobian and its tranpose conjugate
    SLC_PArray_t _jtworkT, _jtcworkT, _ycvworkT; // transposed work area for matrix multiplication
    SLC_PArray_t _jtc_j; // product of transconj Jacobian and the Jacobian.
    SLC_PArray_t  _inv_jtc_j; // and its inverse.
    SLC_PArray_t _jtc_y; // prouct of transconj Jacobian and _y.
    SLC_PArray_t _invwork; // work matrix for inverting matrices
    
    // convergence cliterion
    SLC_r64_t _normDeltaX, _normY;

    // operating state
    SLC_NLSLState_t state;
    SLC_size_t iter;
    NLSLGNSolverTracer64 traceIXY, traceIJ, traceINormDXNormY;
};

#define SAFEFREE(__var) if (__var) { free(__var); __var = NULL; }
void FreeAllArraysr64(SLC_PNLSLGNSolverr64_t solver)
{
    SAFEFREE(solver->_xcv);
    SAFEFREE(solver->_xcv_new);
    SAFEFREE(solver->_delta_xcv);
    SAFEFREE(solver->_xcv_workT);
    SAFEFREE(solver->_ycv);
    SAFEFREE(solver->_jcolbuf);
    SAFEFREE(solver->_j);
    SAFEFREE(solver->_jtc);
    SAFEFREE(solver->_jtworkT);
    SAFEFREE(solver->_jtcworkT);
    SAFEFREE(solver->_ycvworkT);
    SAFEFREE(solver->_jtc_j);
    SAFEFREE(solver->_inv_jtc_j);
    SAFEFREE(solver->_jtc_y);
    SAFEFREE(solver->_invwork);
}
#undef SAFEFREE
#pragma region Trace_methods_are_private_to_this_source_code 
static void NLSLGNSolverTracer64_None(SLC_PNLSLGNSolverr64_t solver)
{
    // does nothing
}

static void NLSLGNSolverTracer64_IXY(SLC_PNLSLGNSolverr64_t solver)
{
    SLC_PArray_t x = solver->_xcv;
    SLC_PArray_t y = solver->_ycv;
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    fprintf(trace_out, "x={");
    for (SLC_i16_t i = 0; i < x->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_r64_print(trace_out, delimiter, x->data._r64[i]);
    }
    fprintf(trace_out, "}\ny={");
    for (SLC_i16_t i = 0; i < y->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_r64_print(trace_out, delimiter, y->data._r64[i]);
    }
    fprintf(trace_out, "}\n");
}

static void NLSLGNSolverTracer64_IJ(SLC_PNLSLGNSolverr64_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_Matr64_Print(trace_out, "Jacobian: ", solver->_j, "");
}

static void NLSLGNSolverTracer64_INormDXNormY(SLC_PNLSLGNSolverr64_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_r64_print(trace_out, "norm(delta-x) = ", solver->_normDeltaX);
    SLC_r64_print(trace_out, "\tnorm(y) = ", solver->_normY);
    fprintf(trace_out, "\n");
}
#pragma endregion Trace_methods_are_private_to_this_source_code 

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverr64_t SLC_NLSLGNSolverr64_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PNLSLGNSolverr64_t p = NULL;
    do {
        SLC_size_t alloc_size_core = SLC_ALIGN8(sizeof(SLC_NLSLGNSolverr64_t));
        SLC_size_t alloc_size_jacobian = SLC_ALIGN8(sizeof(SLC_GVVF_r64) * cx);
        SLC_size_t alloc_size = alloc_size_core + alloc_size_jacobian;
        p = (SLC_PNLSLGNSolverr64_t)aligned_alloc(8, alloc_size);
        SLC_IfNullERR(p, err, __FILE__, __func__, __LINE__);
        p->conf.base.trace.trace_out = stdout;
        p->conf.base.trace.item = NLSLTraceItem_None;
        p->conf.base.cx = cx;
        p->conf.base.cy = cy;
        p->conf.base.cc = cc;
        p->conf.base.maxIter = 100;
        p->conf.base.c = p->conf.base.xInitial = NULL;
        p->conf.base.dxNormMax = cx * SLC_r64_stdtol;
        p->conf.base.yNormMax = cy * (SLC_r64_stdtol * (SLC_r64_t)1000);
        p->conf.base.objective = NULL;
        p->conf.jacobian = (SLC_GVVF_r64*)((SLC_u8_t*)p + alloc_size_core);
        p->state = NLSLState_created;
        p->iter = 0;
        p->traceINormDXNormY = p->traceIJ = p->traceIXY = NLSLGNSolverTracer64_None;
    } while (0);
    return p;
}

// delete an existing instance
void SLC_NLSLGNSolverr64_Delete(SLC_PNLSLGNSolverr64_t *ppsolver)
{
    assert(ppsolver && *ppsolver);
    SLC_PNLSLGNSolverr64_t p = *ppsolver;
    FreeAllArraysr64(p);
    free(p);
    *ppsolver = NULL;
}

// retrieve a configuration struct
SLC_PNLSLGNConfr64_t SLC_NLSLGNSolverr64_Conf(SLC_PNLSLGNSolverr64_t solver)
{
    return &solver->conf;
}

static void NLSLGNSolverr64_InitTrace(SLC_PNLSLGNSolverr64_t solver)
{
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IXY))
    {
        solver->traceIXY = NLSLGNSolverTracer64_IXY;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IJ))
    {
        solver->traceIJ = NLSLGNSolverTracer64_IJ;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_INormDXNormY))
    {
        solver->traceINormDXNormY = NLSLGNSolverTracer64_INormDXNormY;
    }
}

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverr64_Init(SLC_PNLSLGNSolverr64_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_i16_t unit_size = sizeof(SLC_r64_t);
    assert(solver->conf.base.objective);
    assert(solver->conf.base.cc > 0 && solver->conf.base.c); // const parameters has been initialized.
    for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
    {
        assert(solver->conf.jacobian[i]);
    }
    do {
        { // init _xcv, _xcv_new, _ycv, _ycvworkT
            SLC_4i16_t xcv_size = { unit_size, 1, solver->conf.base.cx, 1 };
            SLC_4i16_t transposed_xcv_size = SLC_TransposedMatSize(xcv_size);
            SLC_4i16_t ycv_size = { unit_size, 1, solver->conf.base.cy, 1 };
            SLC_4i16_t transposed_ycv_size = SLC_TransposedMatSize(ycv_size);
            SLC_IfNullERR(solver->_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_delta_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_new = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_workT = SLC_Array_Alloc(transposed_xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycv = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jcolbuf = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycvworkT = SLC_Array_Alloc(transposed_ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc_y = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
        } { // init _j, _jtc, _jtworkT, _jtcworkT
            SLC_4i16_t jsize = { unit_size, solver->conf.base.cx, solver->conf.base.cy, 1 };
            SLC_4i16_t jtcsize = SLC_TransposedMatSize(jsize);
            SLC_IfNullERR(solver->_j = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtworkT = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtcworkT = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
        } { // init _jtc_j, _inv_jtc_j, _invwork
            SLC_4i16_t jtc_j_size = { unit_size, solver->conf.base.cx, solver->conf.base.cx, 1 };
            SLC_4i16_t invwork_size = SLC_InvMatWorkSize(jtc_j_size);
            SLC_IfNullERR(solver->_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_inv_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_invwork = SLC_Array_Alloc(invwork_size), err, __FILE__, __func__, __LINE__);
        }
        SLC_r64_copy(solver->_xcv->data._r64, 1, solver->conf.base.xInitial, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._r64, solver->conf.base.cy,
            solver->_xcv->data._r64, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        solver->state = (err) ? NLSLState_errabort : NLSLState_initialized;
        solver->iter = 0;
        NLSLGNSolverr64_InitTrace(solver);
    } while (0);
    if (err) FreeAllArraysr64(solver);
    return err;
}

// calculate new X vector
SLC_errno_t RenewXr64(SLC_PNLSLGNSolverr64_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_size_t jacobian_columns = solver->conf.base.cx;
        SLC_size_t jacobian_rows = solver->conf.base.cy;
        for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
        {
            err = solver->conf.jacobian[i](
                solver->_jcolbuf->data._r64, solver->conf.base.cy,
                solver->_xcv->data._r64, solver->conf.base.cx,
                solver->conf.base.c, solver->conf.base.cc
            );
            if (err)
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            SLC_r64_copy(solver->_j->data._r64 + i, jacobian_columns,
                solver->_jcolbuf->data._r64, 1, jacobian_rows);
        }
        if (err) break;
        SLC_Matr64_TransConj(solver->_jtc, solver->_j);
        SLC_Matr64_Mul(solver->_jtc_j, solver->_jtc, solver->_j, solver->_jtworkT);
        SLC_Matr64_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        err = SLC_Matr64_Inv(solver->_inv_jtc_j, solver->_jtc_j, solver->_invwork);
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            break;
        }
        SLC_Matr64_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        SLC_Matr64_Mul(solver->_delta_xcv, solver->_inv_jtc_j, solver->_jtc_y, solver->_xcv_workT);
        SLC_Matr64_ScaleAdd(solver->_xcv_new, solver->_xcv, &SLC_r64_units[1], 
            solver->_delta_xcv, &SLC_r64_units[2]);
        SLC_r64_copy(solver->_xcv->data._r64, 1, solver->_xcv_new->data._r64, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._r64, solver->conf.base.cy,
            solver->_xcv->data._r64, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            solver->state = NLSLState_errabort;
            break;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_NLSLGNSolverr64_Execute(SLC_PNLSLGNSolverr64_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        solver->state = NLSLState_running;
        for (; solver->iter < solver->conf.base.maxIter; solver->iter++)
        {
            solver->traceIXY(solver); // debug trace
            // calculating a new X vector to update solver->_xcv_new.
            if (EXIT_SUCCESS != (err = RenewXr64(solver)))
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            solver->traceIJ(solver); // debug trace
            // check delta-x convergence
            solver->_normDeltaX = SLC_r64_abssum(solver->_delta_xcv->data._r64, solver->conf.base.cx);
            solver->_normY = SLC_r64_abssum(solver->_ycv->data._r64, solver->conf.base.cy);
            solver->traceINormDXNormY(solver); // debug trace
            if ((solver->_normDeltaX < solver->conf.base.dxNormMax) && (solver->_normY < solver->conf.base.yNormMax))
            {
                solver->state = NLSLState_converged;
                break;
            }
        }
        if (solver->iter == solver->conf.base.maxIter)
        {
            err = SLC_ENOCONV;
            solver->state = NLSLState_iterlimit;
        }
    } while (0);
    return err;
}

// retrieve x and y vector
const SLC_r64_t* SLC_NLSLGNSolverr64_X(SLC_PNLSLGNSolverr64_t solver) { return solver->_xcv->data._r64; }
const SLC_r64_t* SLC_NLSLGNSolverr64_Y(SLC_PNLSLGNSolverr64_t solver) { return solver->_ycv->data._r64; }

// retrieve L1 norm of dx and y vector
SLC_r64_t SLC_NLSLGNSolverr64_L1NormDX(SLC_PNLSLGNSolverr64_t solver) { return solver->_normDeltaX; }
SLC_r64_t SLC_NLSLGNSolverr64_L1NormY(SLC_PNLSLGNSolverr64_t solver) { return solver->_normY; }

#pragma endregion SLC_NLSLGNSolverr64_implimentation

#pragma region SLC_NLSLGNSolverc64_implimentation
typedef void (*NLSLGNSolverTracec64)(SLC_PNLSLGNSolverc64_t solver);

struct SLC_NLSLGNSolverc64 {
    // configuration parameters
    SLC_NLSLGNConfc64_t conf;

    // working matrices
    SLC_PArray_t 
        _xcv_new, // renewed _xcv
        _xcv, // X column vector
        _delta_xcv, // 
        _xcv_workT, // transposed _xcv size matrix for work area
        _ycv, // Y column vector
        _jcolbuf, // Jacobian column buffer
        _j, _jtc; // Jacobian and its tranpose conjugate
    SLC_PArray_t _jtworkT, _jtcworkT, _ycvworkT; // transposed work area for matrix multiplication
    SLC_PArray_t _jtc_j; // product of transconj Jacobian and the Jacobian.
    SLC_PArray_t  _inv_jtc_j; // and its inverse.
    SLC_PArray_t _jtc_y; // prouct of transconj Jacobian and _y.
    SLC_PArray_t _invwork; // work matrix for inverting matrices
    
    // convergence cliterion
    SLC_r32_t _normDeltaX, _normY;

    // operating state
    SLC_NLSLState_t state;
    SLC_size_t iter;
    NLSLGNSolverTracec64 traceIXY, traceIJ, traceINormDXNormY;
};

#define SAFEFREE(__var) if (__var) { free(__var); __var = NULL; }
void FreeAllArraysc64(SLC_PNLSLGNSolverc64_t solver)
{
    SAFEFREE(solver->_xcv);
    SAFEFREE(solver->_xcv_new);
    SAFEFREE(solver->_delta_xcv);
    SAFEFREE(solver->_xcv_workT);
    SAFEFREE(solver->_ycv);
    SAFEFREE(solver->_jcolbuf);
    SAFEFREE(solver->_j);
    SAFEFREE(solver->_jtc);
    SAFEFREE(solver->_jtworkT);
    SAFEFREE(solver->_jtcworkT);
    SAFEFREE(solver->_ycvworkT);
    SAFEFREE(solver->_jtc_j);
    SAFEFREE(solver->_inv_jtc_j);
    SAFEFREE(solver->_jtc_y);
    SAFEFREE(solver->_invwork);
}
#undef SAFEFREE
#pragma region Trace_methods_are_private_to_this_source_code 
static void NLSLGNSolverTracec64_None(SLC_PNLSLGNSolverc64_t solver)
{
    // does nothing
}

static void NLSLGNSolverTracec64_IXY(SLC_PNLSLGNSolverc64_t solver)
{
    SLC_PArray_t x = solver->_xcv;
    SLC_PArray_t y = solver->_ycv;
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    fprintf(trace_out, "x={");
    for (SLC_i16_t i = 0; i < x->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_c64_print(trace_out, delimiter, x->data._c64[i]);
    }
    fprintf(trace_out, "}\ny={");
    for (SLC_i16_t i = 0; i < y->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_c64_print(trace_out, delimiter, y->data._c64[i]);
    }
    fprintf(trace_out, "}\n");
}

static void NLSLGNSolverTracec64_IJ(SLC_PNLSLGNSolverc64_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_Matc64_Print(trace_out, "Jacobian: ", solver->_j, "");
}

static void NLSLGNSolverTracec64_INormDXNormY(SLC_PNLSLGNSolverc64_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_r32_print(trace_out, "norm(delta-x) = ", solver->_normDeltaX);
    SLC_r32_print(trace_out, "\tnorm(y) = ", solver->_normY);
    fprintf(trace_out, "\n");
}
#pragma endregion Trace_methods_are_private_to_this_source_code 

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverc64_t SLC_NLSLGNSolverc64_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PNLSLGNSolverc64_t p = NULL;
    do {
        SLC_size_t alloc_size_core = SLC_ALIGN8(sizeof(SLC_NLSLGNSolverc64_t));
        SLC_size_t alloc_size_jacobian = SLC_ALIGN8(sizeof(SLC_GVVF_c64) * cx);
        SLC_size_t alloc_size = alloc_size_core + alloc_size_jacobian;
        p = (SLC_PNLSLGNSolverc64_t)aligned_alloc(8, alloc_size);
        SLC_IfNullERR(p, err, __FILE__, __func__, __LINE__);
        p->conf.base.trace.trace_out = stdout;
        p->conf.base.trace.item = NLSLTraceItem_None;
        p->conf.base.cx = cx;
        p->conf.base.cy = cy;
        p->conf.base.cc = cc;
        p->conf.base.maxIter = 100;
        p->conf.base.c = p->conf.base.xInitial = NULL;
        p->conf.base.dxNormMax = cx * SLC_c64_stdtol;
        p->conf.base.yNormMax = cy * (SLC_c64_stdtol * (SLC_r32_t)1000);
        p->conf.base.objective = NULL;
        p->conf.jacobian = (SLC_GVVF_c64*)((SLC_u8_t*)p + alloc_size_core);
        p->state = NLSLState_created;
        p->iter = 0;
        p->traceINormDXNormY = p->traceIJ = p->traceIXY = NLSLGNSolverTracec64_None;
    } while (0);
    return p;
}

// delete an existing instance
void SLC_NLSLGNSolverc64_Delete(SLC_PNLSLGNSolverc64_t *ppsolver)
{
    assert(ppsolver && *ppsolver);
    SLC_PNLSLGNSolverc64_t p = *ppsolver;
    FreeAllArraysc64(p);
    free(p);
    *ppsolver = NULL;
}

// retrieve a configuration struct
SLC_PNLSLGNConfc64_t SLC_NLSLGNSolverc64_Conf(SLC_PNLSLGNSolverc64_t solver)
{
    return &solver->conf;
}

static void NLSLGNSolverc64_InitTrace(SLC_PNLSLGNSolverc64_t solver)
{
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IXY))
    {
        solver->traceIXY = NLSLGNSolverTracec64_IXY;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IJ))
    {
        solver->traceIJ = NLSLGNSolverTracec64_IJ;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_INormDXNormY))
    {
        solver->traceINormDXNormY = NLSLGNSolverTracec64_INormDXNormY;
    }
}

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverc64_Init(SLC_PNLSLGNSolverc64_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_i16_t unit_size = sizeof(SLC_c64_t);
    assert(solver->conf.base.objective);
    assert(solver->conf.base.cc > 0 && solver->conf.base.c); // const parameters has been initialized.
    for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
    {
        assert(solver->conf.jacobian[i]);
    }
    do {
        { // init _xcv, _xcv_new, _ycv, _ycvworkT
            SLC_4i16_t xcv_size = { unit_size, 1, solver->conf.base.cx, 1 };
            SLC_4i16_t transposed_xcv_size = SLC_TransposedMatSize(xcv_size);
            SLC_4i16_t ycv_size = { unit_size, 1, solver->conf.base.cy, 1 };
            SLC_4i16_t transposed_ycv_size = SLC_TransposedMatSize(ycv_size);
            SLC_IfNullERR(solver->_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_delta_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_new = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_workT = SLC_Array_Alloc(transposed_xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycv = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jcolbuf = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycvworkT = SLC_Array_Alloc(transposed_ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc_y = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
        } { // init _j, _jtc, _jtworkT, _jtcworkT
            SLC_4i16_t jsize = { unit_size, solver->conf.base.cx, solver->conf.base.cy, 1 };
            SLC_4i16_t jtcsize = SLC_TransposedMatSize(jsize);
            SLC_IfNullERR(solver->_j = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtworkT = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtcworkT = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
        } { // init _jtc_j, _inv_jtc_j, _invwork
            SLC_4i16_t jtc_j_size = { unit_size, solver->conf.base.cx, solver->conf.base.cx, 1 };
            SLC_4i16_t invwork_size = SLC_InvMatWorkSize(jtc_j_size);
            SLC_IfNullERR(solver->_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_inv_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_invwork = SLC_Array_Alloc(invwork_size), err, __FILE__, __func__, __LINE__);
        }
        SLC_c64_copy(solver->_xcv->data._c64, 1, solver->conf.base.xInitial, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._c64, solver->conf.base.cy,
            solver->_xcv->data._c64, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        solver->state = (err) ? NLSLState_errabort : NLSLState_initialized;
        solver->iter = 0;
        NLSLGNSolverc64_InitTrace(solver);
    } while (0);
    if (err) FreeAllArraysc64(solver);
    return err;
}

// calculate new X vector
SLC_errno_t RenewXc64(SLC_PNLSLGNSolverc64_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_size_t jacobian_columns = solver->conf.base.cx;
        SLC_size_t jacobian_rows = solver->conf.base.cy;
        for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
        {
            err = solver->conf.jacobian[i](
                solver->_jcolbuf->data._c64, solver->conf.base.cy,
                solver->_xcv->data._c64, solver->conf.base.cx,
                solver->conf.base.c, solver->conf.base.cc
            );
            if (err)
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            SLC_c64_copy(solver->_j->data._c64 + i, jacobian_columns,
                solver->_jcolbuf->data._c64, 1, jacobian_rows);
        }
        if (err) break;
        SLC_Matc64_TransConj(solver->_jtc, solver->_j);
        SLC_Matc64_Mul(solver->_jtc_j, solver->_jtc, solver->_j, solver->_jtworkT);
        SLC_Matc64_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        err = SLC_Matc64_Inv(solver->_inv_jtc_j, solver->_jtc_j, solver->_invwork);
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            break;
        }
        SLC_Matc64_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        SLC_Matc64_Mul(solver->_delta_xcv, solver->_inv_jtc_j, solver->_jtc_y, solver->_xcv_workT);
        SLC_Matc64_ScaleAdd(solver->_xcv_new, solver->_xcv, &SLC_c64_units[1], 
            solver->_delta_xcv, &SLC_c64_units[2]);
        SLC_c64_copy(solver->_xcv->data._c64, 1, solver->_xcv_new->data._c64, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._c64, solver->conf.base.cy,
            solver->_xcv->data._c64, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            solver->state = NLSLState_errabort;
            break;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_NLSLGNSolverc64_Execute(SLC_PNLSLGNSolverc64_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        solver->state = NLSLState_running;
        for (; solver->iter < solver->conf.base.maxIter; solver->iter++)
        {
            solver->traceIXY(solver); // debug trace
            // calculating a new X vector to update solver->_xcv_new.
            if (EXIT_SUCCESS != (err = RenewXc64(solver)))
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            solver->traceIJ(solver); // debug trace
            // check delta-x convergence
            solver->_normDeltaX = SLC_c64_abssum(solver->_delta_xcv->data._c64, solver->conf.base.cx);
            solver->_normY = SLC_c64_abssum(solver->_ycv->data._c64, solver->conf.base.cy);
            solver->traceINormDXNormY(solver); // debug trace
            if ((solver->_normDeltaX < solver->conf.base.dxNormMax) && (solver->_normY < solver->conf.base.yNormMax))
            {
                solver->state = NLSLState_converged;
                break;
            }
        }
        if (solver->iter == solver->conf.base.maxIter)
        {
            err = SLC_ENOCONV;
            solver->state = NLSLState_iterlimit;
        }
    } while (0);
    return err;
}

// retrieve x and y vector
const SLC_c64_t* SLC_NLSLGNSolverc64_X(SLC_PNLSLGNSolverc64_t solver) { return solver->_xcv->data._c64; }
const SLC_c64_t* SLC_NLSLGNSolverc64_Y(SLC_PNLSLGNSolverc64_t solver) { return solver->_ycv->data._c64; }

// retrieve L1 norm of dx and y vector
SLC_c64_t SLC_NLSLGNSolverc64_L1NormDX(SLC_PNLSLGNSolverc64_t solver) { return solver->_normDeltaX; }
SLC_c64_t SLC_NLSLGNSolverc64_L1NormY(SLC_PNLSLGNSolverc64_t solver) { return solver->_normY; }

#pragma endregion SLC_NLSLGNSolverc64_implimentation

#pragma region SLC_NLSLGNSolverc128_implimentation
typedef void (*NLSLGNSolverTracec128)(SLC_PNLSLGNSolverc128_t solver);

struct SLC_NLSLGNSolverc128 {
    // configuration parameters
    SLC_NLSLGNConfc128_t conf;

    // working matrices
    SLC_PArray_t 
        _xcv_new, // renewed _xcv
        _xcv, // X column vector
        _delta_xcv, // 
        _xcv_workT, // transposed _xcv size matrix for work area
        _ycv, // Y column vector
        _jcolbuf, // Jacobian column buffer
        _j, _jtc; // Jacobian and its tranpose conjugate
    SLC_PArray_t _jtworkT, _jtcworkT, _ycvworkT; // transposed work area for matrix multiplication
    SLC_PArray_t _jtc_j; // product of transconj Jacobian and the Jacobian.
    SLC_PArray_t  _inv_jtc_j; // and its inverse.
    SLC_PArray_t _jtc_y; // prouct of transconj Jacobian and _y.
    SLC_PArray_t _invwork; // work matrix for inverting matrices
    
    // convergence cliterion
    SLC_r64_t _normDeltaX, _normY;

    // operating state
    SLC_NLSLState_t state;
    SLC_size_t iter;
    NLSLGNSolverTracec128 traceIXY, traceIJ, traceINormDXNormY;
};

#define SAFEFREE(__var) if (__var) { free(__var); __var = NULL; }
void FreeAllArraysc128(SLC_PNLSLGNSolverc128_t solver)
{
    SAFEFREE(solver->_xcv);
    SAFEFREE(solver->_xcv_new);
    SAFEFREE(solver->_delta_xcv);
    SAFEFREE(solver->_xcv_workT);
    SAFEFREE(solver->_ycv);
    SAFEFREE(solver->_jcolbuf);
    SAFEFREE(solver->_j);
    SAFEFREE(solver->_jtc);
    SAFEFREE(solver->_jtworkT);
    SAFEFREE(solver->_jtcworkT);
    SAFEFREE(solver->_ycvworkT);
    SAFEFREE(solver->_jtc_j);
    SAFEFREE(solver->_inv_jtc_j);
    SAFEFREE(solver->_jtc_y);
    SAFEFREE(solver->_invwork);
}
#undef SAFEFREE
#pragma region Trace_methods_are_private_to_this_source_code 
static void NLSLGNSolverTracec128_None(SLC_PNLSLGNSolverc128_t solver)
{
    // does nothing
}

static void NLSLGNSolverTracec128_IXY(SLC_PNLSLGNSolverc128_t solver)
{
    SLC_PArray_t x = solver->_xcv;
    SLC_PArray_t y = solver->_ycv;
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    fprintf(trace_out, "x={");
    for (SLC_i16_t i = 0; i < x->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_c128_print(trace_out, delimiter, x->data._c128[i]);
    }
    fprintf(trace_out, "}\ny={");
    for (SLC_i16_t i = 0; i < y->cont.i16[2]; i++)
    {
        const char* delimiter = (i == 0) ? " " : " ,";
        SLC_c128_print(trace_out, delimiter, y->data._c128[i]);
    }
    fprintf(trace_out, "}\n");
}

static void NLSLGNSolverTracec128_IJ(SLC_PNLSLGNSolverc128_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_Matc128_Print(trace_out, "Jacobian: ", solver->_j, "");
}

static void NLSLGNSolverTracec128_INormDXNormY(SLC_PNLSLGNSolverc128_t solver)
{
    FILE* trace_out = solver->conf.base.trace.trace_out;
    fprintf(trace_out, "iter=%ld\n", solver->iter);
    SLC_r64_print(trace_out, "norm(delta-x) = ", solver->_normDeltaX);
    SLC_r64_print(trace_out, "\tnorm(y) = ", solver->_normY);
    fprintf(trace_out, "\n");
}
#pragma endregion Trace_methods_are_private_to_this_source_code 

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverc128_t SLC_NLSLGNSolverc128_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_PNLSLGNSolverc128_t p = NULL;
    do {
        SLC_size_t alloc_size_core = SLC_ALIGN8(sizeof(SLC_NLSLGNSolverc128_t));
        SLC_size_t alloc_size_jacobian = SLC_ALIGN8(sizeof(SLC_GVVF_c128) * cx);
        SLC_size_t alloc_size = alloc_size_core + alloc_size_jacobian;
        p = (SLC_PNLSLGNSolverc128_t)aligned_alloc(8, alloc_size);
        SLC_IfNullERR(p, err, __FILE__, __func__, __LINE__);
        p->conf.base.trace.trace_out = stdout;
        p->conf.base.trace.item = NLSLTraceItem_None;
        p->conf.base.cx = cx;
        p->conf.base.cy = cy;
        p->conf.base.cc = cc;
        p->conf.base.maxIter = 100;
        p->conf.base.c = p->conf.base.xInitial = NULL;
        p->conf.base.dxNormMax = cx * SLC_c128_stdtol;
        p->conf.base.yNormMax = cy * (SLC_c128_stdtol * (SLC_r64_t)1000);
        p->conf.base.objective = NULL;
        p->conf.jacobian = (SLC_GVVF_c128*)((SLC_u8_t*)p + alloc_size_core);
        p->state = NLSLState_created;
        p->iter = 0;
        p->traceINormDXNormY = p->traceIJ = p->traceIXY = NLSLGNSolverTracec128_None;
    } while (0);
    return p;
}

// delete an existing instance
void SLC_NLSLGNSolverc128_Delete(SLC_PNLSLGNSolverc128_t *ppsolver)
{
    assert(ppsolver && *ppsolver);
    SLC_PNLSLGNSolverc128_t p = *ppsolver;
    FreeAllArraysc128(p);
    free(p);
    *ppsolver = NULL;
}

// retrieve a configuration struct
SLC_PNLSLGNConfc128_t SLC_NLSLGNSolverc128_Conf(SLC_PNLSLGNSolverc128_t solver)
{
    return &solver->conf;
}

static void NLSLGNSolverc128_InitTrace(SLC_PNLSLGNSolverc128_t solver)
{
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IXY))
    {
        solver->traceIXY = NLSLGNSolverTracec128_IXY;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_IJ))
    {
        solver->traceIJ = NLSLGNSolverTracec128_IJ;
    }
    if (0 != (solver->conf.base.trace.item & NLSLTraceItem_INormDXNormY))
    {
        solver->traceINormDXNormY = NLSLGNSolverTracec128_INormDXNormY;
    }
}

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverc128_Init(SLC_PNLSLGNSolverc128_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_i16_t unit_size = sizeof(SLC_c128_t);
    assert(solver->conf.base.objective);
    assert(solver->conf.base.cc > 0 && solver->conf.base.c); // const parameters has been initialized.
    for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
    {
        assert(solver->conf.jacobian[i]);
    }
    do {
        { // init _xcv, _xcv_new, _ycv, _ycvworkT
            SLC_4i16_t xcv_size = { unit_size, 1, solver->conf.base.cx, 1 };
            SLC_4i16_t transposed_xcv_size = SLC_TransposedMatSize(xcv_size);
            SLC_4i16_t ycv_size = { unit_size, 1, solver->conf.base.cy, 1 };
            SLC_4i16_t transposed_ycv_size = SLC_TransposedMatSize(ycv_size);
            SLC_IfNullERR(solver->_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_delta_xcv = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_new = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_xcv_workT = SLC_Array_Alloc(transposed_xcv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycv = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jcolbuf = SLC_Array_Alloc(ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_ycvworkT = SLC_Array_Alloc(transposed_ycv_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc_y = SLC_Array_Alloc(xcv_size), err, __FILE__, __func__, __LINE__);
        } { // init _j, _jtc, _jtworkT, _jtcworkT
            SLC_4i16_t jsize = { unit_size, solver->conf.base.cx, solver->conf.base.cy, 1 };
            SLC_4i16_t jtcsize = SLC_TransposedMatSize(jsize);
            SLC_IfNullERR(solver->_j = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtc = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtworkT = SLC_Array_Alloc(jtcsize), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_jtcworkT = SLC_Array_Alloc(jsize), err, __FILE__, __func__, __LINE__);
        } { // init _jtc_j, _inv_jtc_j, _invwork
            SLC_4i16_t jtc_j_size = { unit_size, solver->conf.base.cx, solver->conf.base.cx, 1 };
            SLC_4i16_t invwork_size = SLC_InvMatWorkSize(jtc_j_size);
            SLC_IfNullERR(solver->_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_inv_jtc_j = SLC_Array_Alloc(jtc_j_size), err, __FILE__, __func__, __LINE__);
            SLC_IfNullERR(solver->_invwork = SLC_Array_Alloc(invwork_size), err, __FILE__, __func__, __LINE__);
        }
        SLC_c128_copy(solver->_xcv->data._c128, 1, solver->conf.base.xInitial, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._c128, solver->conf.base.cy,
            solver->_xcv->data._c128, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        solver->state = (err) ? NLSLState_errabort : NLSLState_initialized;
        solver->iter = 0;
        NLSLGNSolverc128_InitTrace(solver);
    } while (0);
    if (err) FreeAllArraysc128(solver);
    return err;
}

// calculate new X vector
SLC_errno_t RenewXc128(SLC_PNLSLGNSolverc128_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_size_t jacobian_columns = solver->conf.base.cx;
        SLC_size_t jacobian_rows = solver->conf.base.cy;
        for (SLC_size_t i = 0; i < solver->conf.base.cx; i++)
        {
            err = solver->conf.jacobian[i](
                solver->_jcolbuf->data._c128, solver->conf.base.cy,
                solver->_xcv->data._c128, solver->conf.base.cx,
                solver->conf.base.c, solver->conf.base.cc
            );
            if (err)
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            SLC_c128_copy(solver->_j->data._c128 + i, jacobian_columns,
                solver->_jcolbuf->data._c128, 1, jacobian_rows);
        }
        if (err) break;
        SLC_Matc128_TransConj(solver->_jtc, solver->_j);
        SLC_Matc128_Mul(solver->_jtc_j, solver->_jtc, solver->_j, solver->_jtworkT);
        SLC_Matc128_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        err = SLC_Matc128_Inv(solver->_inv_jtc_j, solver->_jtc_j, solver->_invwork);
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            break;
        }
        SLC_Matc128_Mul(solver->_jtc_y, solver->_jtc, solver->_ycv, solver->_ycvworkT);
        SLC_Matc128_Mul(solver->_delta_xcv, solver->_inv_jtc_j, solver->_jtc_y, solver->_xcv_workT);
        SLC_Matc128_ScaleAdd(solver->_xcv_new, solver->_xcv, &SLC_c128_units[1], 
            solver->_delta_xcv, &SLC_c128_units[2]);
        SLC_c128_copy(solver->_xcv->data._c128, 1, solver->_xcv_new->data._c128, 1, solver->conf.base.cx);
        err = solver->conf.base.objective(
            solver->_ycv->data._c128, solver->conf.base.cy,
            solver->_xcv->data._c128, solver->conf.base.cx,
            solver->conf.base.c, solver->conf.base.cc
        );
        if (err != EXIT_SUCCESS)
        {
            SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
            solver->state = NLSLState_errabort;
            break;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_NLSLGNSolverc128_Execute(SLC_PNLSLGNSolverc128_t solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        solver->state = NLSLState_running;
        for (; solver->iter < solver->conf.base.maxIter; solver->iter++)
        {
            solver->traceIXY(solver); // debug trace
            // calculating a new X vector to update solver->_xcv_new.
            if (EXIT_SUCCESS != (err = RenewXc128(solver)))
            {
                SLC_LogERR(err, "@ %s, %s, %d\n", __FILE__, __func__, __LINE__);
                solver->state = NLSLState_errabort;
                break;
            }
            solver->traceIJ(solver); // debug trace
            // check delta-x convergence
            solver->_normDeltaX = SLC_c128_abssum(solver->_delta_xcv->data._c128, solver->conf.base.cx);
            solver->_normY = SLC_c128_abssum(solver->_ycv->data._c128, solver->conf.base.cy);
            solver->traceINormDXNormY(solver); // debug trace
            if ((solver->_normDeltaX < solver->conf.base.dxNormMax) && (solver->_normY < solver->conf.base.yNormMax))
            {
                solver->state = NLSLState_converged;
                break;
            }
        }
        if (solver->iter == solver->conf.base.maxIter)
        {
            err = SLC_ENOCONV;
            solver->state = NLSLState_iterlimit;
        }
    } while (0);
    return err;
}

// retrieve x and y vector
const SLC_c128_t* SLC_NLSLGNSolverc128_X(SLC_PNLSLGNSolverc128_t solver) { return solver->_xcv->data._c128; }
const SLC_c128_t* SLC_NLSLGNSolverc128_Y(SLC_PNLSLGNSolverc128_t solver) { return solver->_ycv->data._c128; }

// retrieve L1 norm of dx and y vector
SLC_c128_t SLC_NLSLGNSolverc128_L1NormDX(SLC_PNLSLGNSolverc128_t solver) { return solver->_normDeltaX; }
SLC_c128_t SLC_NLSLGNSolverc128_L1NormY(SLC_PNLSLGNSolverc128_t solver) { return solver->_normY; }

#pragma endregion SLC_NLSLGNSolverc128_implimentation

