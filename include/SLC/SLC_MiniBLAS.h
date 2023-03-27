#if !defined(_SLC_MINIBLAS_H)
#define _SLC_MINIBLAS_H
#include "SLC/SLC_Numbers.h"

#pragma region r32_functions
void SLC_r32_copyconj(
    SLC_r32_t* dst, SLC_size_t dst_step,
    const SLC_r32_t* src, SLC_size_t src_step,
    SLC_size_t count
);

//--- in-place operation identifiers have postfix 'ip'. ---
// addition (dst += src)
void SLC_r32_addip(SLC_r32_t* dst, const SLC_r32_t* src, SLC_size_t count);

// scaling (dst *= scale)
void SLC_r32_scaleip(SLC_r32_t* dst, const SLC_r32_t* scale, SLC_size_t count);

// scaling addition (dst += src * scale)
void SLC_r32_scaleaddip(SLC_r32_t* dst, const SLC_r32_t* src, const SLC_r32_t* scale, SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_r32_multiplyebeip(SLC_r32_t* dst, const SLC_r32_t* src, SLC_size_t count);

//--- substitutional operation identifiers have postfix 'subs'. ---
// addition
void SLC_r32_addsubs(SLC_r32_t* dst, const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count);

// scaling
void SLC_r32_scalesubs(SLC_r32_t* dst, const SLC_r32_t* src, const SLC_r32_t* scale, SLC_size_t count);

// scaling addition
void SLC_r32_scaleaddsubs(
    SLC_r32_t* dst, 
    const SLC_r32_t* src0, const SLC_r32_t* scale0, 
    const SLC_r32_t* src1, const SLC_r32_t* scale1,
    SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_r32_multyplyebesubs(SLC_r32_t* dst, const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count);

//--- vector-in, scalar-out operation identifier does not have any postfix. ---
// inner product (sum(src0[]*conj(src1[])))
SLC_r32_t SLC_r32_innerproduct(const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count);

// product-sum (sum(src0[]*src1[]))
SLC_r32_t SLC_r32_productsum(const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count);

// sum of elements in an array
SLC_r32_t SLC_r32_sum(const SLC_r32_t* src, SLC_size_t count);

// absolute sum
SLC_r32_t SLC_r32_abssum(const SLC_r32_t* src, SLC_size_t count);
#pragma endregion r32_functions


#pragma region r64_functions
void SLC_r64_copyconj(
    SLC_r64_t* dst, SLC_size_t dst_step,
    const SLC_r64_t* src, SLC_size_t src_step,
    SLC_size_t count
);

//--- in-place operation identifiers have postfix 'ip'. ---
// addition (dst += src)
void SLC_r64_addip(SLC_r64_t* dst, const SLC_r64_t* src, SLC_size_t count);

// scaling (dst *= scale)
void SLC_r64_scaleip(SLC_r64_t* dst, const SLC_r64_t* scale, SLC_size_t count);

// scaling addition (dst += src * scale)
void SLC_r64_scaleaddip(SLC_r64_t* dst, const SLC_r64_t* src, const SLC_r64_t* scale, SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_r64_multiplyebeip(SLC_r64_t* dst, const SLC_r64_t* src, SLC_size_t count);

//--- substitutional operation identifiers have postfix 'subs'. ---
// addition
void SLC_r64_addsubs(SLC_r64_t* dst, const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count);

// scaling
void SLC_r64_scalesubs(SLC_r64_t* dst, const SLC_r64_t* src, const SLC_r64_t* scale, SLC_size_t count);

// scaling addition
void SLC_r64_scaleaddsubs(
    SLC_r64_t* dst, 
    const SLC_r64_t* src0, const SLC_r64_t* scale0, 
    const SLC_r64_t* src1, const SLC_r64_t* scale1,
    SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_r64_multyplyebesubs(SLC_r64_t* dst, const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count);

//--- vector-in, scalar-out operation identifier does not have any postfix. ---
// inner product (sum(src0[]*conj(src1[])))
SLC_r64_t SLC_r64_innerproduct(const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count);

// product-sum (sum(src0[]*src1[]))
SLC_r64_t SLC_r64_productsum(const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count);

// sum of elements in an array
SLC_r64_t SLC_r64_sum(const SLC_r64_t* src, SLC_size_t count);

// absolute sum
SLC_r64_t SLC_r64_abssum(const SLC_r64_t* src, SLC_size_t count);
#pragma endregion r64_functions


#pragma region c64_functions
void SLC_c64_copyconj(
    SLC_c64_t* dst, SLC_size_t dst_step,
    const SLC_c64_t* src, SLC_size_t src_step,
    SLC_size_t count
);

//--- in-place operation identifiers have postfix 'ip'. ---
// addition (dst += src)
void SLC_c64_addip(SLC_c64_t* dst, const SLC_c64_t* src, SLC_size_t count);

// scaling (dst *= scale)
void SLC_c64_scaleip(SLC_c64_t* dst, const SLC_c64_t* scale, SLC_size_t count);

// scaling addition (dst += src * scale)
void SLC_c64_scaleaddip(SLC_c64_t* dst, const SLC_c64_t* src, const SLC_c64_t* scale, SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_c64_multiplyebeip(SLC_c64_t* dst, const SLC_c64_t* src, SLC_size_t count);

//--- substitutional operation identifiers have postfix 'subs'. ---
// addition
void SLC_c64_addsubs(SLC_c64_t* dst, const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count);

// scaling
void SLC_c64_scalesubs(SLC_c64_t* dst, const SLC_c64_t* src, const SLC_c64_t* scale, SLC_size_t count);

// scaling addition
void SLC_c64_scaleaddsubs(
    SLC_c64_t* dst, 
    const SLC_c64_t* src0, const SLC_c64_t* scale0, 
    const SLC_c64_t* src1, const SLC_c64_t* scale1,
    SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_c64_multyplyebesubs(SLC_c64_t* dst, const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count);

//--- vector-in, scalar-out operation identifier does not have any postfix. ---
// inner product (sum(src0[]*conj(src1[])))
SLC_c64_t SLC_c64_innerproduct(const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count);

// product-sum (sum(src0[]*src1[]))
SLC_c64_t SLC_c64_productsum(const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count);

// sum of elements in an array
SLC_c64_t SLC_c64_sum(const SLC_c64_t* src, SLC_size_t count);

// absolute sum
SLC_r32_t SLC_c64_abssum(const SLC_c64_t* src, SLC_size_t count);
#pragma endregion c64_functions


#pragma region c128_functions
void SLC_c128_copyconj(
    SLC_c128_t* dst, SLC_size_t dst_step,
    const SLC_c128_t* src, SLC_size_t src_step,
    SLC_size_t count
);

//--- in-place operation identifiers have postfix 'ip'. ---
// addition (dst += src)
void SLC_c128_addip(SLC_c128_t* dst, const SLC_c128_t* src, SLC_size_t count);

// scaling (dst *= scale)
void SLC_c128_scaleip(SLC_c128_t* dst, const SLC_c128_t* scale, SLC_size_t count);

// scaling addition (dst += src * scale)
void SLC_c128_scaleaddip(SLC_c128_t* dst, const SLC_c128_t* src, const SLC_c128_t* scale, SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_c128_multiplyebeip(SLC_c128_t* dst, const SLC_c128_t* src, SLC_size_t count);

//--- substitutional operation identifiers have postfix 'subs'. ---
// addition
void SLC_c128_addsubs(SLC_c128_t* dst, const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count);

// scaling
void SLC_c128_scalesubs(SLC_c128_t* dst, const SLC_c128_t* src, const SLC_c128_t* scale, SLC_size_t count);

// scaling addition
void SLC_c128_scaleaddsubs(
    SLC_c128_t* dst, 
    const SLC_c128_t* src0, const SLC_c128_t* scale0, 
    const SLC_c128_t* src1, const SLC_c128_t* scale1,
    SLC_size_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element product
void SLC_c128_multyplyebesubs(SLC_c128_t* dst, const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count);

//--- vector-in, scalar-out operation identifier does not have any postfix. ---
// inner product (sum(src0[]*conj(src1[])))
SLC_c128_t SLC_c128_innerproduct(const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count);

// product-sum (sum(src0[]*src1[]))
SLC_c128_t SLC_c128_productsum(const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count);

// sum of elements in an array
SLC_c128_t SLC_c128_sum(const SLC_c128_t* src, SLC_size_t count);

// absolute sum
SLC_r64_t SLC_c128_abssum(const SLC_c128_t* src, SLC_size_t count);
#pragma endregion c128_functions


#endif
