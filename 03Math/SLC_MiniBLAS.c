#include "SLC/SLC_MiniBLAS.h"

#pragma region r32_functions
void SLC_r32_copyconj(
    SLC_r32_t* dst, SLC_size_t dst_step,
    const SLC_r32_t* src, SLC_size_t src_step,
    SLC_size_t count
) {
    for (SLC_size_t i = 0; i < count; i++)
    {
        *dst = SLC_r32_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

void SLC_r32_addip(SLC_r32_t* dst, const SLC_r32_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index];
    }
}

void SLC_r32_scaleip(SLC_r32_t* dst, const SLC_r32_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= *scale;
    }
}

void SLC_r32_scaleaddip(
    SLC_r32_t* dst, const SLC_r32_t* src, const SLC_r32_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index] * (*scale);
    }
}

void SLC_r32_multiplyebeip(SLC_r32_t* dst, const SLC_r32_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= src[index];
    }
}

void SLC_r32_addsubs(
    SLC_r32_t* dst, const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

void SLC_r32_scaleaddsubs(
    SLC_r32_t* dst, 
    const SLC_r32_t* src0, const SLC_r32_t* scale0, 
    const SLC_r32_t* src1, const SLC_r32_t* scale1,
    SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * (*scale0) + src1[index] * (*scale1);
    }
}

void SLC_r32_multyplyebesubs(
    SLC_r32_t* dst, const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

SLC_r32_t SLC_r32_innerproduct(
    const SLC_r32_t* src0, const SLC_r32_t* src1, SLC_size_t count
) {
    SLC_r32_t dst = SLC_r32_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src0[index] * src1[index];
    }
    return dst;
}

SLC_r32_t SLC_r32_sum(const SLC_r32_t* src, SLC_size_t count)
{
    SLC_r32_t dst = SLC_r32_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src[index];
    }
    return dst;
}

SLC_r32_t SLC_r32_abssum(const SLC_r32_t* src, SLC_size_t count)
{
    SLC_r32_t dst = SLC_r32_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += SLC_r32_abs(src[index]);
    }
    return dst;
}
#pragma endregion r32_functions

#pragma region r64_functions
void SLC_r64_copyconj(
    SLC_r64_t* dst, SLC_size_t dst_step,
    const SLC_r64_t* src, SLC_size_t src_step,
    SLC_size_t count
) {
    for (SLC_size_t i = 0; i < count; i++)
    {
        *dst = SLC_r64_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

void SLC_r64_addip(SLC_r64_t* dst, const SLC_r64_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index];
    }
}

void SLC_r64_scaleip(SLC_r64_t* dst, const SLC_r64_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= *scale;
    }
}

void SLC_r64_scaleaddip(
    SLC_r64_t* dst, const SLC_r64_t* src, const SLC_r64_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index] * (*scale);
    }
}

void SLC_r64_multiplyebeip(SLC_r64_t* dst, const SLC_r64_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= src[index];
    }
}

void SLC_r64_addsubs(
    SLC_r64_t* dst, const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

void SLC_r64_scaleaddsubs(
    SLC_r64_t* dst, 
    const SLC_r64_t* src0, const SLC_r64_t* scale0, 
    const SLC_r64_t* src1, const SLC_r64_t* scale1,
    SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * (*scale0) + src1[index] * (*scale1);
    }
}

void SLC_r64_multyplyebesubs(
    SLC_r64_t* dst, const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

SLC_r64_t SLC_r64_innerproduct(
    const SLC_r64_t* src0, const SLC_r64_t* src1, SLC_size_t count
) {
    SLC_r64_t dst = SLC_r64_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src0[index] * src1[index];
    }
    return dst;
}

SLC_r64_t SLC_r64_sum(const SLC_r64_t* src, SLC_size_t count)
{
    SLC_r64_t dst = SLC_r64_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src[index];
    }
    return dst;
}

SLC_r64_t SLC_r64_abssum(const SLC_r64_t* src, SLC_size_t count)
{
    SLC_r64_t dst = SLC_r64_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += SLC_r64_abs(src[index]);
    }
    return dst;
}
#pragma endregion r64_functions

#pragma region c64_functions
void SLC_c64_copyconj(
    SLC_c64_t* dst, SLC_size_t dst_step,
    const SLC_c64_t* src, SLC_size_t src_step,
    SLC_size_t count
) {
    for (SLC_size_t i = 0; i < count; i++)
    {
        *dst = SLC_c64_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

void SLC_c64_addip(SLC_c64_t* dst, const SLC_c64_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index];
    }
}

void SLC_c64_scaleip(SLC_c64_t* dst, const SLC_c64_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= *scale;
    }
}

void SLC_c64_scaleaddip(
    SLC_c64_t* dst, const SLC_c64_t* src, const SLC_c64_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index] * (*scale);
    }
}

void SLC_c64_multiplyebeip(SLC_c64_t* dst, const SLC_c64_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= src[index];
    }
}

void SLC_c64_addsubs(
    SLC_c64_t* dst, const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

void SLC_c64_scaleaddsubs(
    SLC_c64_t* dst, 
    const SLC_c64_t* src0, const SLC_c64_t* scale0, 
    const SLC_c64_t* src1, const SLC_c64_t* scale1,
    SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * (*scale0) + src1[index] * (*scale1);
    }
}

void SLC_c64_multyplyebesubs(
    SLC_c64_t* dst, const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

SLC_c64_t SLC_c64_innerproduct(
    const SLC_c64_t* src0, const SLC_c64_t* src1, SLC_size_t count
) {
    SLC_c64_t dst = SLC_c64_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src0[index] * src1[index];
    }
    return dst;
}

SLC_c64_t SLC_c64_sum(const SLC_c64_t* src, SLC_size_t count)
{
    SLC_c64_t dst = SLC_c64_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src[index];
    }
    return dst;
}

SLC_r32_t SLC_c64_abssum(const SLC_c64_t* src, SLC_size_t count)
{
    SLC_r32_t dst = SLC_r32_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += SLC_c64_abs(src[index]);
    }
    return dst;
}
#pragma endregion c64_functions

#pragma region c128_functions
void SLC_c128_copyconj(
    SLC_c128_t* dst, SLC_size_t dst_step,
    const SLC_c128_t* src, SLC_size_t src_step,
    SLC_size_t count
) {
    for (SLC_size_t i = 0; i < count; i++)
    {
        *dst = SLC_c128_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

void SLC_c128_addip(SLC_c128_t* dst, const SLC_c128_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index];
    }
}

void SLC_c128_scaleip(SLC_c128_t* dst, const SLC_c128_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= *scale;
    }
}

void SLC_c128_scaleaddip(
    SLC_c128_t* dst, const SLC_c128_t* src, const SLC_c128_t* scale, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] += src[index] * (*scale);
    }
}

void SLC_c128_multiplyebeip(SLC_c128_t* dst, const SLC_c128_t* src, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] *= src[index];
    }
}

void SLC_c128_addsubs(
    SLC_c128_t* dst, const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count)
{
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

void SLC_c128_scaleaddsubs(
    SLC_c128_t* dst, 
    const SLC_c128_t* src0, const SLC_c128_t* scale0, 
    const SLC_c128_t* src1, const SLC_c128_t* scale1,
    SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * (*scale0) + src1[index] * (*scale1);
    }
}

void SLC_c128_multyplyebesubs(
    SLC_c128_t* dst, const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count
) {
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst[index] = src0[index] * src1[index];
    }
}

SLC_c128_t SLC_c128_innerproduct(
    const SLC_c128_t* src0, const SLC_c128_t* src1, SLC_size_t count
) {
    SLC_c128_t dst = SLC_c128_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src0[index] * src1[index];
    }
    return dst;
}

SLC_c128_t SLC_c128_sum(const SLC_c128_t* src, SLC_size_t count)
{
    SLC_c128_t dst = SLC_c128_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += src[index];
    }
    return dst;
}

SLC_r64_t SLC_c128_abssum(const SLC_c128_t* src, SLC_size_t count)
{
    SLC_r64_t dst = SLC_r64_units[0];
    for (SLC_size_t index = 0; index < count; index++)
    {
        dst += SLC_c128_abs(src[index]);
    }
    return dst;
}
#pragma endregion c128_functions

