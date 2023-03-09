# MiniLA defines LAPACK like functions but not compatible.
## Matrix representation
Matrix is defined by `SLC_Array_t`. Matrix layout is always row-major except special case.
In such case, matrix usage is documented for each case.

## APIs
The following list is written in generic type. <NTID> is one of
* `SLC_r32_t` (`float`),
* `SLC_r64_t` (`double`),
* `SLC_c64_t` (`float complex`),
* `SLC_c128_t` (`double complex`).

Matrix size consistency is checked by assert only in debug build.
Size check must be done explicitly if necessary in runtime.

```
void SLC_Mat<NTID>_Add(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1);
void SLC_Mat<NTID>_AddScale(SLC_PArray_t dst, SLC_PArray_t src0, const SLC_<NTID>_t* scale0,
    SLC_PArray_t src1, const SLC_<NTID>_t* scale1);
void SLC_Mat<NTID>_Scale(SLC_PArray_t dst, SLC_PArray_t src, const SLC_<NTID>_t *scale);
void SLC_Mat<NTID>_Mul(SLC_PArray_t dst, SLC_PArray_t src0, SLC_PArray_t src1, SLC_PArray_t work);
void SLC_Mat<NTID>_Transpose(SLC_PArray_t dst, SLC_PArray_t src);
void SLC_Mat<NTID>_Inv(SLC_PArray_t dst, SLC_PArray_t src, SLC_PArray_t work);
// solve fully determined linear equation
// left * dst = right,
// left, right: known matrix
// dst: unknown solution
void SLC_Mat<NTID>_Solve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT_left, SLC_PArray_t work);
void SLC_Mat<NTID>_EasySolve(SLC_PArray_t dst, SLC_PArray_t left, SLC_PArray_t right,
    SLC_PArray_t leftT_left);

// solve overdetermined linear equation
void SLC_Mat<NTID>_EasySolveOD(SLC_PArray_t dst, SLC_PArray_t leftT, SLC_PArray_t right);
void SLC_Mat<NTID>_SolveOD(SLC_PArray_t dst, SLC_PArray_t leftT, SLC_PArray_t right,
    SLC_PArray_t rightT, SLC_PArray_t leftT_left, SLC_PArray_t leftT_right, SLC_PArray_t work);

// QR decomposition
void SLC_Mat<NTID>_QRD(SLC_PArray_t dst, SLC_PArray_t src);
```