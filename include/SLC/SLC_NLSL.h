#if !defined(_SLC_NLSL_H)
#define _SLC_NLSL_H
#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_errno.h"
typedef enum {
NLSLState_created, // created but not yet initialized
NLSLState_initialized, // just after initialized
NLSLState_running, // running execution
NLSLState_iterlimit, // stopped by iteration limit
NLSLState_converged, // stopped by convergence
NLSLState_errabort, // stopped by error in objective or Jacobian
} SLC_NLSLState_t;

typedef SLC_errno_t (*SLC_GVVF_r32)(
    SLC_r32_t* y, SLC_size_t cy, /* depedent variables */
    const SLC_r32_t* x, SLC_size_t cx, /* independent variables */
    const SLC_r32_t* c, SLC_size_t cc /* constants */);

typedef struct {
    SLC_size_t cx, cy, cc; /* element counts of x, y, c */
    SLC_size_t maxIter; /* maximum iteration limit */
    SLC_r32_t *xInitial; /* initial x vector */
    SLC_r32_t *c; /* constant parameters of objective function and jacobian */
    SLC_r32_t dxNormMax, yNormMax; /* Convergence criterions; L1 norm of delta-x and y */
    SLC_GVVF_r32 objective; /* objective function */
} SLC_NLSLConfr32_t, *SLC_PNLSLConfr32_t;

typedef SLC_errno_t (*SLC_GVVF_r64)(
    SLC_r64_t* y, SLC_size_t cy, /* depedent variables */
    const SLC_r64_t* x, SLC_size_t cx, /* independent variables */
    const SLC_r64_t* c, SLC_size_t cc /* constants */);

typedef struct {
    SLC_size_t cx, cy, cc; /* element counts of x, y, c */
    SLC_size_t maxIter; /* maximum iteration limit */
    SLC_r64_t *xInitial; /* initial x vector */
    SLC_r64_t *c; /* constant parameters of objective function and jacobian */
    SLC_r64_t dxNormMax, yNormMax; /* Convergence criterions; L1 norm of delta-x and y */
    SLC_GVVF_r64 objective; /* objective function */
} SLC_NLSLConfr64_t, *SLC_PNLSLConfr64_t;

typedef SLC_errno_t (*SLC_GVVF_c64)(
    SLC_c64_t* y, SLC_size_t cy, /* depedent variables */
    const SLC_c64_t* x, SLC_size_t cx, /* independent variables */
    const SLC_c64_t* c, SLC_size_t cc /* constants */);

typedef struct {
    SLC_size_t cx, cy, cc; /* element counts of x, y, c */
    SLC_size_t maxIter; /* maximum iteration limit */
    SLC_c64_t *xInitial; /* initial x vector */
    SLC_c64_t *c; /* constant parameters of objective function and jacobian */
    SLC_r32_t dxNormMax, yNormMax; /* Convergence criterions; L1 norm of delta-x and y */
    SLC_GVVF_c64 objective; /* objective function */
} SLC_NLSLConfc64_t, *SLC_PNLSLConfc64_t;

typedef SLC_errno_t (*SLC_GVVF_c128)(
    SLC_c128_t* y, SLC_size_t cy, /* depedent variables */
    const SLC_c128_t* x, SLC_size_t cx, /* independent variables */
    const SLC_c128_t* c, SLC_size_t cc /* constants */);

typedef struct {
    SLC_size_t cx, cy, cc; /* element counts of x, y, c */
    SLC_size_t maxIter; /* maximum iteration limit */
    SLC_c128_t *xInitial; /* initial x vector */
    SLC_c128_t *c; /* constant parameters of objective function and jacobian */
    SLC_r64_t dxNormMax, yNormMax; /* Convergence criterions; L1 norm of delta-x and y */
    SLC_GVVF_c128 objective; /* objective function */
} SLC_NLSLConfc128_t, *SLC_PNLSLConfc128_t;

#endif
