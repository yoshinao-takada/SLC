#include "SLC/SLC_NumbersCopy.h"
#include <memory.h>
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

void SLC_i8_swap(
    SLC_i8_t* x0, SLC_i8_t* x1, SLC_i8_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_i8_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_i16_swap(
    SLC_i16_t* x0, SLC_i16_t* x1, SLC_i16_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_i16_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_i32_swap(
    SLC_i32_t* x0, SLC_i32_t* x1, SLC_i32_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_i32_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_i64_swap(
    SLC_i64_t* x0, SLC_i64_t* x1, SLC_i64_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_i64_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_u8_swap(
    SLC_u8_t* x0, SLC_u8_t* x1, SLC_u8_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_u8_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_u16_swap(
    SLC_u16_t* x0, SLC_u16_t* x1, SLC_u16_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_u16_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_u32_swap(
    SLC_u32_t* x0, SLC_u32_t* x1, SLC_u32_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_u32_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_u64_swap(
    SLC_u64_t* x0, SLC_u64_t* x1, SLC_u64_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_u64_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_r32_swap(
    SLC_r32_t* x0, SLC_r32_t* x1, SLC_r32_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_r32_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_r64_swap(
    SLC_r64_t* x0, SLC_r64_t* x1, SLC_r64_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_r64_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_c64_swap(
    SLC_c64_t* x0, SLC_c64_t* x1, SLC_c64_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_c64_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_c128_swap(
    SLC_c128_t* x0, SLC_c128_t* x1, SLC_c128_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_c128_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
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

void SLC_bool_swap(
    SLC_bool_t* x0, SLC_bool_t* x1, SLC_bool_t* temp, SLC_size_t count
) {
    SLC_size_t copy_size = count * sizeof(SLC_bool_t);
    memcpy(temp, x0, copy_size);
    memcpy(x0, x1, copy_size);
    memcpy(x1, temp, copy_size);
}

