#if !defined(_SLC_NUMBERCOPY_H)
#define _SLC_NUMBERCOPY_H
#include "SLC/SLC_Numbers.h"
void SLC_i8_copy(
    SLC_i8_t* dst, SLC_size_t dst_step,
    const SLC_i8_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_i8_set0(
    SLC_i8_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i8_set1(
    SLC_i8_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i16_copy(
    SLC_i16_t* dst, SLC_size_t dst_step,
    const SLC_i16_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_i16_set0(
    SLC_i16_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i16_set1(
    SLC_i16_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i32_copy(
    SLC_i32_t* dst, SLC_size_t dst_step,
    const SLC_i32_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_i32_set0(
    SLC_i32_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i32_set1(
    SLC_i32_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i64_copy(
    SLC_i64_t* dst, SLC_size_t dst_step,
    const SLC_i64_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_i64_set0(
    SLC_i64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_i64_set1(
    SLC_i64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u8_copy(
    SLC_u8_t* dst, SLC_size_t dst_step,
    const SLC_u8_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_u8_set0(
    SLC_u8_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u8_set1(
    SLC_u8_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u16_copy(
    SLC_u16_t* dst, SLC_size_t dst_step,
    const SLC_u16_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_u16_set0(
    SLC_u16_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u16_set1(
    SLC_u16_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u32_copy(
    SLC_u32_t* dst, SLC_size_t dst_step,
    const SLC_u32_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_u32_set0(
    SLC_u32_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u32_set1(
    SLC_u32_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u64_copy(
    SLC_u64_t* dst, SLC_size_t dst_step,
    const SLC_u64_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_u64_set0(
    SLC_u64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_u64_set1(
    SLC_u64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_r32_copy(
    SLC_r32_t* dst, SLC_size_t dst_step,
    const SLC_r32_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_r32_set0(
    SLC_r32_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_r32_set1(
    SLC_r32_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_r64_copy(
    SLC_r64_t* dst, SLC_size_t dst_step,
    const SLC_r64_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_r64_set0(
    SLC_r64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_r64_set1(
    SLC_r64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_c64_copy(
    SLC_c64_t* dst, SLC_size_t dst_step,
    const SLC_c64_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_c64_set0(
    SLC_c64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_c64_set1(
    SLC_c64_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_c128_copy(
    SLC_c128_t* dst, SLC_size_t dst_step,
    const SLC_c128_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_c128_set0(
    SLC_c128_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_c128_set1(
    SLC_c128_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_bool_copy(
    SLC_bool_t* dst, SLC_size_t dst_step,
    const SLC_bool_t* src, SLC_size_t src_step,
    SLC_size_t count
);

void SLC_bool_set0(
    SLC_bool_t* dst, SLC_size_t dst_step, SLC_size_t count);

void SLC_bool_set1(
    SLC_bool_t* dst, SLC_size_t dst_step, SLC_size_t count);

#endif
