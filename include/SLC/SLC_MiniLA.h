#if !defined(_SLC_MINILA_H)
#define _SLC_MINILA_H
#include "SLC/SLC_Array.h"
#include "SLC/SLC_errno.h"

#pragma region r32_functions
void SLC_Matr32_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1);
void SLC_Matr32_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_r32_t* scale0,
    SLC_PArray_t src1, const SLC_r32_t* scale1);
void SLC_Matr32_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_r32_t *scale);
void SLC_Matr32_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work);
void SLC_Matr32_Transpose(SLC_PArray_t dst, SLC_PArray_t src);
void SLC_Matr32_TransConj(SLC_PArray_t dst, SLC_PArray_t src);
SLC_errno_t SLC_Matr32_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work);
// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matr32_Solve(
    SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work);
SLC_errno_t SLC_Matr32_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);

// solve overdetermined linear equation
SLC_errno_t SLC_Matr32_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);
SLC_errno_t SLC_Matr32_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work);

// QR decomposition
void SLC_Matr32_QRD(SLC_PArray_t dst, SLC_PArray_t src);

// Human readable print
void SLC_Matr32_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer);
#pragma endregion r32_functions

#pragma region r64_functions
void SLC_Matr64_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1);
void SLC_Matr64_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_r64_t* scale0,
    SLC_PArray_t src1, const SLC_r64_t* scale1);
void SLC_Matr64_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_r64_t *scale);
void SLC_Matr64_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work);
void SLC_Matr64_Transpose(SLC_PArray_t dst, SLC_PArray_t src);
void SLC_Matr64_TransConj(SLC_PArray_t dst, SLC_PArray_t src);
SLC_errno_t SLC_Matr64_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work);
// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matr64_Solve(
    SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work);
SLC_errno_t SLC_Matr64_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);

// solve overdetermined linear equation
SLC_errno_t SLC_Matr64_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);
SLC_errno_t SLC_Matr64_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work);

// QR decomposition
void SLC_Matr64_QRD(SLC_PArray_t dst, SLC_PArray_t src);

// Human readable print
void SLC_Matr64_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer);
#pragma endregion r64_functions

#pragma region c64_functions
void SLC_Matc64_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1);
void SLC_Matc64_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_c64_t* scale0,
    SLC_PArray_t src1, const SLC_c64_t* scale1);
void SLC_Matc64_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_c64_t *scale);
void SLC_Matc64_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work);
void SLC_Matc64_Transpose(SLC_PArray_t dst, SLC_PArray_t src);
void SLC_Matc64_TransConj(SLC_PArray_t dst, SLC_PArray_t src);
SLC_errno_t SLC_Matc64_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work);
// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matc64_Solve(
    SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work);
SLC_errno_t SLC_Matc64_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);

// solve overdetermined linear equation
SLC_errno_t SLC_Matc64_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);
SLC_errno_t SLC_Matc64_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work);

// QR decomposition
void SLC_Matc64_QRD(SLC_PArray_t dst, SLC_PArray_t src);

// Human readable print
void SLC_Matc64_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer);
#pragma endregion c64_functions

#pragma region c128_functions
void SLC_Matc128_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1);
void SLC_Matc128_ScaleAdd(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_c128_t* scale0,
    SLC_PArray_t src1, const SLC_c128_t* scale1);
void SLC_Matc128_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_c128_t *scale);
void SLC_Matc128_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work);
void SLC_Matc128_Transpose(SLC_PArray_t dst, SLC_PArray_t src);
void SLC_Matc128_TransConj(SLC_PArray_t dst, SLC_PArray_t src);
SLC_errno_t SLC_Matc128_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work);
// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
SLC_errno_t SLC_Matc128_Solve(
    SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right, SLC_PArray_t work);
SLC_errno_t SLC_Matc128_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);

// solve overdetermined linear equation
SLC_errno_t SLC_Matc128_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right);
SLC_errno_t SLC_Matc128_SolveOD(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT, SLC_PArray_t leftTC, SLC_PArray_t leftTC_left,
    SLC_PArray_t rightT, SLC_PArray_t leftTC_right,
    SLC_PArray_t work);

// QR decomposition
void SLC_Matc128_QRD(SLC_PArray_t dst, SLC_PArray_t src);

// Human readable print
void SLC_Matc128_Print(FILE* out, const char* header, SLC_PArray_t mat, const char* footer);
#pragma endregion c128_functions

#endif
