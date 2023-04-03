# Nonlinear Solver (NLSL)
## Overview
Two types of NLSL are defined.
* Gauss-Newton method: applicable only to differentiable functions.
* Nelder-Mead method: applicable to any continuous functions including spline functions like broken-line.


## Gauss-Newton Method
I thought that the most understandable formulation is presented in a topic,
**"_k_ variables, _k_ functions"** and
**"_k_ variables, _m_ equations, with _m_&nbsp;&gt;&nbsp;_k_"** in
[a Wikipedia article](https://en.wikipedia.org/wiki/Newton%27s_method).

Mathematical details are described in [README-gaussnewton.md](README-gaussnewton.md)  

## Generic Parts of Nonlinear Solvers
Most of Nonlinear solvers execute iterative operations and operation states a
defined in a header file, `SLC/SLC_NLSLCommon.h`.
```
// Nonlineaer solver states
typedef enum {
    NLSLState_created, // created but not initialized
    NLSLState_initialized, // just after initialized
    NLSLState_running, // running execution
    NLSLState_iterlimit, // stopped by iteration limit
    NLSLState_converged, // stopped by convergence
    NLSLState_errabort, // stopped by error in objective or Jacobian
} SLC_NLSLState_t;
```
Generic Nonlinear solvers have objective functions as defined below.
Configuration parameters depend on algorithms. But many of the parameters are common to most algorithms.
The common parts of the parameter and objective function signature are also defined below.
```
typedef SLC_errno_t (*SLC_GVVF_<NTID>)(
    SLC_<NTID>_t* y, SLC_size_t cy, /* depedent variables */
    const SLC_<NTID>_t* x, SLC_size_t cx, /* dependent variables */
    const SLC_<NTID>_t* c, SLC_size_t cc /* constants */);

typedef struct {
    SLC_size_t cx, cy, cc; /* element counts of x, y, c */
    SLC_size_t maxIter; /* maximum iteration limit */
    SLC_<NTID>_t *xInitial; /* initial x vector */
    SLC_<RTID>_t dxNormMax, yNormMax; /* Convergence criterions; L1 norm of delta-x and y */
    SLC_GVVF_<NTID> objective; /* objective function */
} SLC_NLSLConf<NTID>_t, *SLC_PNLSLConf<NTID>_t;
```
* `cx` : dimension of independent variable __x__,
* `cy` : dimension of objective function dependent varialble, __y__,
* `cc` : count of constants,
* `maxIter` : it limits iteration of Gauss-Newton method iterative operation,
* `dxNormMax` : convergence criteria of deviation of __x__ in (_i_ + 1)th iteration and _i_th iteration.
The criteria is evaluated as an L1-norm (absolute some of the deviation).
* `yNormMax` : convergence criteria of __y__ which is evaluated if the deviation of __x__ satisfies its criteria.
* `objective` : function pointer to an objective function.
, where "&lt;NTID&gt;" is one of "r32", "r64", "c64", and "c128". "&lt;RTID&gt;" is one of "r32" or "r64".
The identifiers represent number types as listed below.

Table. Number type identifiers
Identifier | SLC number type | std-C number type
-----------|-----------------|------------------
r32        | SLC_r32_t       | float
r64        | SLC_r64_t       | double
c64        | SLC_c64_t       | float complex
c128       | SLC_c128_t      | double complex
<br/>

## Gauss-Newton Method Solver Implementation
Configuration struct for Gauss-Newton method is derived from the common configuration `SLC_NLSLConf<NTID>_t`. 

```
typedef struct {
    SLC_NLSLConf<NTID>_t base; // configuration common parts are regarded as a base class.
    SLC_GVVF_<NTID>* jacobian; /* Jacobian column vector functions */
} SLC_NLSLGNConf<NTID>_t, *SLC_PNLSLGNConf<NTID>_t;
```
Main body of Gauss-Newton solver contains many matrices and complicated.
Therefore its details are hidden in its c source file and are not shown in any header files.
```
typedef struct SLC_NLSLGNSolver<NTID> SLC_NLSLGNSolver<NTID>_t;
typedef SLC_NLSLGNSolver<NTID>_t *SLC_PNLSLGNSolver<NTID>_t;
```

Methods comprising the Gauss-Newton solver are declared as shown below.
```
// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolver<NTID>_t SLC_NLSLGNSolver<NTID>_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc);

// delete an existing instance
void SLC_NLSLGNSolver<NTID>_Delete(SLC_PNLSLGNSolver<NTID>_t *ppsolver);

// retrieve a configuration struct
SLC_PNLSLGNConf<NTID>_t SLC_NLSLGNSolver<NTID>_Conf(SLC_PNLSLGNSolver<NTID>_t solver);

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolver<NTID>_Init(SLC_PNLSLGNSolver<NTID>_t solver);

// execute Gauss-Newton iterative operation
SLC_errno_t SLC_NLSLGNSolver<NTID>_Execute(SLC_PNLSLGNSolver<NTID>_t solver);

// retrieve x and y vector
const SLC_<NTID>_t* SLC_NLSLGNSolver<NTID>_X(SLC_PNLSLGNSolver<NTID>_t solver);
const SLC_<NTID>_t* SLC_NLSLGNSolver<NTID>_Y(SLC_PNLSLGNSolver<NTID>_t solver);

// retrieve L1 norm of dx and y vector
SLC_<NTID>_t SLC_NLSLGNSolver<NTID>_L1NormDX(SLC_PNLSLGNSolver<NTID>_t solver);
SLC_<NTID>_t SLC_NLSLGNSolver<NTID>_L1NormY(SLC_PNLSLGNSolver<NTID>_t solver);
```


## Nelder-Mead method