#if !defined(_SLC_NLSLGN_H)
#define _SLC_NLSLGN_H
#include "SLC/SLC_NLSL.h"
#pragma region Gauss-Newton-Solver-For-SLC_r32_t
typedef struct {
    SLC_NLSLConfr32_t base; // configuration common parts are regarded as a base class.
    SLC_GVVF_r32* jacobian; /* Jacobian column vector functions */
} SLC_NLSLGNConfr32_t, *SLC_PNLSLGNConfr32_t;

typedef struct SLC_NLSLGNSolverr32 SLC_NLSLGNSolverr32_t;
typedef SLC_NLSLGNSolverr32_t *SLC_PNLSLGNSolverr32_t;

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverr32_t SLC_NLSLGNSolverr32_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc);

// delete an existing instance
void SLC_NLSLGNSolverr32_Delete(SLC_PNLSLGNSolverr32_t *ppsolver);

// retrieve a configuration struct
SLC_PNLSLGNConfr32_t SLC_NLSLGNSolverr32_Conf(SLC_PNLSLGNSolverr32_t solver);

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverr32_Init(SLC_PNLSLGNSolverr32_t solver);

// execute Gauss-Newton iterative operation
SLC_errno_t SLC_NLSLGNSolverr32_Execute(SLC_PNLSLGNSolverr32_t solver);

// retrieve x and y vector
const SLC_r32_t* SLC_NLSLGNSolverr32_X(SLC_PNLSLGNSolverr32_t solver);
const SLC_r32_t* SLC_NLSLGNSolverr32_Y(SLC_PNLSLGNSolverr32_t solver);

// retrieve L1 norm of dx and y vector
SLC_r32_t SLC_NLSLGNSolverr32_L1NormDX(SLC_PNLSLGNSolverr32_t solver);
SLC_r32_t SLC_NLSLGNSolverr32_L1NormY(SLC_PNLSLGNSolverr32_t solver);
#pragma endregion Gauss-Newton-Solver-For-SLC_r32_t
#pragma region Gauss-Newton-Solver-For-SLC_r64_t
typedef struct {
    SLC_NLSLConfr64_t base; // configuration common parts are regarded as a base class.
    SLC_GVVF_r64* jacobian; /* Jacobian column vector functions */
} SLC_NLSLGNConfr64_t, *SLC_PNLSLGNConfr64_t;

typedef struct SLC_NLSLGNSolverr64 SLC_NLSLGNSolverr64_t;
typedef SLC_NLSLGNSolverr64_t *SLC_PNLSLGNSolverr64_t;

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverr64_t SLC_NLSLGNSolverr64_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc);

// delete an existing instance
void SLC_NLSLGNSolverr64_Delete(SLC_PNLSLGNSolverr64_t *ppsolver);

// retrieve a configuration struct
SLC_PNLSLGNConfr64_t SLC_NLSLGNSolverr64_Conf(SLC_PNLSLGNSolverr64_t solver);

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverr64_Init(SLC_PNLSLGNSolverr64_t solver);

// execute Gauss-Newton iterative operation
SLC_errno_t SLC_NLSLGNSolverr64_Execute(SLC_PNLSLGNSolverr64_t solver);

// retrieve x and y vector
const SLC_r64_t* SLC_NLSLGNSolverr64_X(SLC_PNLSLGNSolverr64_t solver);
const SLC_r64_t* SLC_NLSLGNSolverr64_Y(SLC_PNLSLGNSolverr64_t solver);

// retrieve L1 norm of dx and y vector
SLC_r64_t SLC_NLSLGNSolverr64_L1NormDX(SLC_PNLSLGNSolverr64_t solver);
SLC_r64_t SLC_NLSLGNSolverr64_L1NormY(SLC_PNLSLGNSolverr64_t solver);
#pragma endregion Gauss-Newton-Solver-For-SLC_r64_t
#pragma region Gauss-Newton-Solver-For-SLC_c64_t
typedef struct {
    SLC_NLSLConfc64_t base; // configuration common parts are regarded as a base class.
    SLC_GVVF_c64* jacobian; /* Jacobian column vector functions */
} SLC_NLSLGNConfc64_t, *SLC_PNLSLGNConfc64_t;

typedef struct SLC_NLSLGNSolverc64 SLC_NLSLGNSolverc64_t;
typedef SLC_NLSLGNSolverc64_t *SLC_PNLSLGNSolverc64_t;

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverc64_t SLC_NLSLGNSolverc64_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc);

// delete an existing instance
void SLC_NLSLGNSolverc64_Delete(SLC_PNLSLGNSolverc64_t *ppsolver);

// retrieve a configuration struct
SLC_PNLSLGNConfc64_t SLC_NLSLGNSolverc64_Conf(SLC_PNLSLGNSolverc64_t solver);

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverc64_Init(SLC_PNLSLGNSolverc64_t solver);

// execute Gauss-Newton iterative operation
SLC_errno_t SLC_NLSLGNSolverc64_Execute(SLC_PNLSLGNSolverc64_t solver);

// retrieve x and y vector
const SLC_c64_t* SLC_NLSLGNSolverc64_X(SLC_PNLSLGNSolverc64_t solver);
const SLC_c64_t* SLC_NLSLGNSolverc64_Y(SLC_PNLSLGNSolverc64_t solver);

// retrieve L1 norm of dx and y vector
SLC_c64_t SLC_NLSLGNSolverc64_L1NormDX(SLC_PNLSLGNSolverc64_t solver);
SLC_c64_t SLC_NLSLGNSolverc64_L1NormY(SLC_PNLSLGNSolverc64_t solver);
#pragma endregion Gauss-Newton-Solver-For-SLC_c64_t
#pragma region Gauss-Newton-Solver-For-SLC_c128_t
typedef struct {
    SLC_NLSLConfc128_t base; // configuration common parts are regarded as a base class.
    SLC_GVVF_c128* jacobian; /* Jacobian column vector functions */
} SLC_NLSLGNConfc128_t, *SLC_PNLSLGNConfc128_t;

typedef struct SLC_NLSLGNSolverc128 SLC_NLSLGNSolverc128_t;
typedef SLC_NLSLGNSolverc128_t *SLC_PNLSLGNSolverc128_t;

// create a new instance of a Gauss-Newton solver
SLC_PNLSLGNSolverc128_t SLC_NLSLGNSolverc128_New(SLC_size_t cx, SLC_size_t cy, SLC_size_t cc);

// delete an existing instance
void SLC_NLSLGNSolverc128_Delete(SLC_PNLSLGNSolverc128_t *ppsolver);

// retrieve a configuration struct
SLC_PNLSLGNConfc128_t SLC_NLSLGNSolverc128_Conf(SLC_PNLSLGNSolverc128_t solver);

// initalizer is called after setting configuration parameters.
SLC_errno_t SLC_NLSLGNSolverc128_Init(SLC_PNLSLGNSolverc128_t solver);

// execute Gauss-Newton iterative operation
SLC_errno_t SLC_NLSLGNSolverc128_Execute(SLC_PNLSLGNSolverc128_t solver);

// retrieve x and y vector
const SLC_c128_t* SLC_NLSLGNSolverc128_X(SLC_PNLSLGNSolverc128_t solver);
const SLC_c128_t* SLC_NLSLGNSolverc128_Y(SLC_PNLSLGNSolverc128_t solver);

// retrieve L1 norm of dx and y vector
SLC_c128_t SLC_NLSLGNSolverc128_L1NormDX(SLC_PNLSLGNSolverc128_t solver);
SLC_c128_t SLC_NLSLGNSolverc128_L1NormY(SLC_PNLSLGNSolverc128_t solver);
#pragma endregion Gauss-Newton-Solver-For-SLC_c128_t
#endif
