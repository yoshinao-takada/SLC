# MiniBLAS
## Overview
`MiniBLAS` is a BLAS like (not compatible but simpler) linear algebraic basic subroutines.

## Functions
```
// in-place operation
// addition (dst += src)
void SLC_<NTID>_addip(SLC_<NTID>_t* dst, const SLC_<NTID>_t* src, SLC_<ITID>_t count);

// scaling (dst *= scale)
void SLC_<NTID>_scaleip(SLC_<NTID>_t* dst, const SLC_<NTID>_t* scale, SLC_<ITID>_t count);

// scaling addition (dst += src * scale)
void SLC_<NTID>_scaleaddip(SLC_<NTID>_t* dst, const SLC_<NTID>_t* src, const SLC_<NTID>_t* scale, SLC_<ITID>_t count);

// element-by-element product
void SLC_<NTID>_multiplyebeip(SLC_<NTID>_t* dst, const SLC_<NTID>_t* src, SLC_<ITID>_t count);

// substitutional operation
// addition
void SLC_<NTID>_addsubs(SLC_<NTID>_t* dst, const SLC_<NTID>_t* src0, const SLC_<NTID>_t* src1, SLC_<ITID>_t count);

// scaling
void SLC_<NTID>_scalesubs(SLC_<NTID>_t* dst, const SLC_<NTID>_t* src, const SLC_<NTID>_t* scale, SLC_<ITID>_t count);

// scaling addition
void SLC_<NTID>_scalesubs(
    SLC_<NTID>_t* dst, 
    const SLC_<NTID>_t* src0, const SLC_<NTID>_t* scale0, 
    const SLC_<NTID>_t* src1, const SLC_<NTID>_t* scale1,
    SLC_<ITID>_t count);

// element-by-element product
void SLC_<NTID>_multyplyebesubs(SLC_<NTID>_t* dst, const SLC_<NTID>_t* src0, const SLC_<NTID>_t* src1, SLC_<ITID>_t count);

// inner product
SLC_<NTID>_t SLC_<NTID>_innerproduct(const SLC_<NTID>_t* src0, const SLC_<NTID>_t* src1, SLC_<ITID>_t count);

// sum of elements in an array
SLC_<NTID>_t SLC_<NTID>_sum(const SLC_<NTID>_t* src, SLC_<ITID>_t count);

// absolute sum
SLC_<NTID>_t SLC_<NTID>_abssum(const SLC_<NTID>_t* src, SLC_<ITID>_t count);
```