#define _SLC_NUMBERS_C
#include "SLC/SLC_Numbers.h"

SLC_i8_t SLC_i8_units[3] = { 0, 1, -1 };

SLC_i16_t SLC_i16_units[3] = { 0, 1, -1 };

SLC_i32_t SLC_i32_units[3] = { 0, 1, -1 };

SLC_i64_t SLC_i64_units[3] = { 0, 1, -1 };

SLC_u8_t SLC_u8_units[2] = { 0, 1 };

SLC_u16_t SLC_u16_units[2] = { 0, 1 };

SLC_u32_t SLC_u32_units[2] = { 0, 1 };

SLC_u64_t SLC_u64_units[2] = { 0, 1 };

SLC_r32_t SLC_r32_units[3] = { 0.0f, 1.0f, -1.0f };

SLC_r64_t SLC_r64_units[3] = { 0.0, 1.0, -1.0 };

SLC_c64_t SLC_c64_units[5] = { 
    CMPLXF(0.0f, 0.0f),
    CMPLXF(1.0f, 0.0f), CMPLXF(-1.0f, 0.0f),
    CMPLXF(0.0f, 1.0f), CMPLXF(0.0f, -1.0f) };


SLC_c128_t SLC_c128_units[5] = { 
    CMPLX(0.0, 0.0),
    CMPLX(1.0, 0.0), CMPLX(-1.0, 0.0),
    CMPLX(0.0, 1.0), CMPLX(0.0, -1.0) };

SLC_bool_t SLC_bool_units[2] = { false, true };

SLC_size_t SLC_unitsizes[] = SLC_UNIT_SIZES;