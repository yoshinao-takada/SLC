#include "SLC/SLC_NumbersCopy.h"
#define _IT	SLC_size_t


void SLC_i8_copy(
    SLC_i8_t* dst, _IT dst_step,
    const SLC_i8_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_i8_set0(
    SLC_i8_t* dst, _IT dst_step, _IT count
) {
    SLC_i8_copy(dst, dst_step, SLC_i8_units, 0, count);
}

void SLC_i8_set1(
    SLC_i8_t* dst, _IT dst_step, _IT count
) {
    SLC_i8_copy(dst, dst_step, SLC_i8_units + 1, 0, count);
}

void SLC_i16_copy(
    SLC_i16_t* dst, _IT dst_step,
    const SLC_i16_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_i16_set0(
    SLC_i16_t* dst, _IT dst_step, _IT count
) {
    SLC_i16_copy(dst, dst_step, SLC_i16_units, 0, count);
}

void SLC_i16_set1(
    SLC_i16_t* dst, _IT dst_step, _IT count
) {
    SLC_i16_copy(dst, dst_step, SLC_i16_units + 1, 0, count);
}

void SLC_i32_copy(
    SLC_i32_t* dst, _IT dst_step,
    const SLC_i32_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_i32_set0(
    SLC_i32_t* dst, _IT dst_step, _IT count
) {
    SLC_i32_copy(dst, dst_step, SLC_i32_units, 0, count);
}

void SLC_i32_set1(
    SLC_i32_t* dst, _IT dst_step, _IT count
) {
    SLC_i32_copy(dst, dst_step, SLC_i32_units + 1, 0, count);
}

void SLC_i64_copy(
    SLC_i64_t* dst, _IT dst_step,
    const SLC_i64_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_i64_set0(
    SLC_i64_t* dst, _IT dst_step, _IT count
) {
    SLC_i64_copy(dst, dst_step, SLC_i64_units, 0, count);
}

void SLC_i64_set1(
    SLC_i64_t* dst, _IT dst_step, _IT count
) {
    SLC_i64_copy(dst, dst_step, SLC_i64_units + 1, 0, count);
}

void SLC_u8_copy(
    SLC_u8_t* dst, _IT dst_step,
    const SLC_u8_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_u8_set0(
    SLC_u8_t* dst, _IT dst_step, _IT count
) {
    SLC_u8_copy(dst, dst_step, SLC_u8_units, 0, count);
}

void SLC_u8_set1(
    SLC_u8_t* dst, _IT dst_step, _IT count
) {
    SLC_u8_copy(dst, dst_step, SLC_u8_units + 1, 0, count);
}

void SLC_u16_copy(
    SLC_u16_t* dst, _IT dst_step,
    const SLC_u16_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_u16_set0(
    SLC_u16_t* dst, _IT dst_step, _IT count
) {
    SLC_u16_copy(dst, dst_step, SLC_u16_units, 0, count);
}

void SLC_u16_set1(
    SLC_u16_t* dst, _IT dst_step, _IT count
) {
    SLC_u16_copy(dst, dst_step, SLC_u16_units + 1, 0, count);
}

void SLC_u32_copy(
    SLC_u32_t* dst, _IT dst_step,
    const SLC_u32_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_u32_set0(
    SLC_u32_t* dst, _IT dst_step, _IT count
) {
    SLC_u32_copy(dst, dst_step, SLC_u32_units, 0, count);
}

void SLC_u32_set1(
    SLC_u32_t* dst, _IT dst_step, _IT count
) {
    SLC_u32_copy(dst, dst_step, SLC_u32_units + 1, 0, count);
}

void SLC_u64_copy(
    SLC_u64_t* dst, _IT dst_step,
    const SLC_u64_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_u64_set0(
    SLC_u64_t* dst, _IT dst_step, _IT count
) {
    SLC_u64_copy(dst, dst_step, SLC_u64_units, 0, count);
}

void SLC_u64_set1(
    SLC_u64_t* dst, _IT dst_step, _IT count
) {
    SLC_u64_copy(dst, dst_step, SLC_u64_units + 1, 0, count);
}

void SLC_r32_copy(
    SLC_r32_t* dst, _IT dst_step,
    const SLC_r32_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_r32_set0(
    SLC_r32_t* dst, _IT dst_step, _IT count
) {
    SLC_r32_copy(dst, dst_step, SLC_r32_units, 0, count);
}

void SLC_r32_set1(
    SLC_r32_t* dst, _IT dst_step, _IT count
) {
    SLC_r32_copy(dst, dst_step, SLC_r32_units + 1, 0, count);
}

void SLC_r64_copy(
    SLC_r64_t* dst, _IT dst_step,
    const SLC_r64_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_r64_set0(
    SLC_r64_t* dst, _IT dst_step, _IT count
) {
    SLC_r64_copy(dst, dst_step, SLC_r64_units, 0, count);
}

void SLC_r64_set1(
    SLC_r64_t* dst, _IT dst_step, _IT count
) {
    SLC_r64_copy(dst, dst_step, SLC_r64_units + 1, 0, count);
}

void SLC_c64_copy(
    SLC_c64_t* dst, _IT dst_step,
    const SLC_c64_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_c64_set0(
    SLC_c64_t* dst, _IT dst_step, _IT count
) {
    SLC_c64_copy(dst, dst_step, SLC_c64_units, 0, count);
}

void SLC_c64_set1(
    SLC_c64_t* dst, _IT dst_step, _IT count
) {
    SLC_c64_copy(dst, dst_step, SLC_c64_units + 1, 0, count);
}

void SLC_c128_copy(
    SLC_c128_t* dst, _IT dst_step,
    const SLC_c128_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_c128_set0(
    SLC_c128_t* dst, _IT dst_step, _IT count
) {
    SLC_c128_copy(dst, dst_step, SLC_c128_units, 0, count);
}

void SLC_c128_set1(
    SLC_c128_t* dst, _IT dst_step, _IT count
) {
    SLC_c128_copy(dst, dst_step, SLC_c128_units + 1, 0, count);
}

void SLC_bool_copy(
    SLC_bool_t* dst, _IT dst_step,
    const SLC_bool_t* src, _IT src_step,
    _IT count
) {
    for (_IT i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dst_step;
        src += src_step;
    }
}

void SLC_bool_set0(
    SLC_bool_t* dst, _IT dst_step, _IT count
) {
    SLC_bool_copy(dst, dst_step, SLC_bool_units, 0, count);
}

void SLC_bool_set1(
    SLC_bool_t* dst, _IT dst_step, _IT count
) {
    SLC_bool_copy(dst, dst_step, SLC_bool_units + 1, 0, count);
}
