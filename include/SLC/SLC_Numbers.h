#if !defined(_SLC_NUMBERS_H)
#define _SLC_NUMBERS_H
#include <stdint.h>
#include <float.h>
#include <complex.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

typedef enum {
    SLC_i8 = 0,
    SLC_i16,
    SLC_i32,
    SLC_i64,
    SLC_u8,
    SLC_u16,
    SLC_u32,
    SLC_u64,
    SLC_r32,
    SLC_r64,
    SLC_c64,
    SLC_c128,
    SLC_size,
    SLC_bool,
    SLC_ptr,
} SLC_NumberType_t;

#pragma region unit_number_types
typedef int8_t SLC_i8_t;
typedef int16_t SLC_i16_t;
typedef int32_t SLC_i32_t;
typedef int64_t SLC_i64_t;
typedef uint8_t SLC_u8_t;
typedef uint16_t SLC_u16_t;
typedef uint32_t SLC_u32_t;
typedef uint64_t SLC_u64_t;
typedef float SLC_r32_t;
typedef double SLC_r64_t;
typedef float complex SLC_c64_t;
typedef double complex SLC_c128_t;
typedef size_t SLC_size_t;
typedef bool SLC_bool_t;
typedef void* SLC_ptr_t;
#pragma endregion

#define SLC_UNIT_SIZES { \
    1, 2, 3, 4, 1, 2, 3, 4, \
    4, 8, 8, 16, sizeof(SLC_size_t), sizeof(SLC_bool_t), sizeof(SLC_ptr_t) }

#pragma region two_element_array_type
typedef int8_t SLC_2i8_t[2];
typedef int16_t SLC_2i16_t[2];
typedef int32_t SLC_2i32_t[2];
typedef int64_t SLC_2i64_t[2];
typedef uint8_t SLC_2u8_t[2];
typedef uint16_t SLC_2u16_t[2];
typedef uint32_t SLC_2u32_t[2];
typedef uint64_t SLC_2u64_t[2];
typedef float SLC_2r32_t[2];
typedef double SLC_2r64_t[2];
typedef float complex SLC_2c64_t[2];
typedef double complex SLC_2c128_t[2];
typedef size_t SLC_2size_t[2];
typedef bool SLC_2bool_t[2];
typedef void* SLC_2ptr_t[2];
#pragma endregion
#pragma region three_element_array_type
typedef int8_t SLC_3i8_t[3];
typedef int16_t SLC_3i16_t[3];
typedef int32_t SLC_3i32_t[3];
typedef int64_t SLC_3i64_t[3];
typedef uint8_t SLC_3u8_t[3];
typedef uint16_t SLC_3u16_t[3];
typedef uint32_t SLC_3u32_t[3];
typedef uint64_t SLC_3u64_t[3];
typedef float SLC_3r32_t[3];
typedef double SLC_3r64_t[3];
typedef float complex SLC_3c64_t[3];
typedef double complex SLC_3c128_t[3];
typedef size_t SLC_3size_t[3];
typedef bool SLC_3bool_t[3];
typedef void* SLC_3ptr_t[3];
#pragma endregion
#pragma region four_element_array_type
typedef int8_t SLC_4i8_t[4];
typedef int16_t SLC_4i16_t[4];
typedef int32_t SLC_4i32_t[4];
typedef int64_t SLC_4i64_t[4];
typedef uint8_t SLC_4u8_t[4];
typedef uint16_t SLC_4u16_t[4];
typedef uint32_t SLC_4u32_t[4];
typedef uint64_t SLC_4u64_t[4];
typedef float SLC_4r32_t[4];
typedef double SLC_4r64_t[4];
typedef float complex SLC_4c64_t[4];
typedef double complex SLC_4c128_t[4];
typedef size_t SLC_4size_t[4];
typedef bool SLC_4bool_t[4];
typedef void* SLC_4ptr_t[4];
#pragma endregion
#pragma region eight_element_array_type
typedef int8_t SLC_8i8_t[8];
typedef int16_t SLC_8i16_t[8];
typedef int32_t SLC_8i32_t[8];
typedef int64_t SLC_8i64_t[8];
typedef uint8_t SLC_8u8_t[8];
typedef uint16_t SLC_8u16_t[8];
typedef uint32_t SLC_8u32_t[8];
typedef uint64_t SLC_8u64_t[8];
typedef float SLC_8r32_t[8];
typedef double SLC_8r64_t[8];
typedef float complex SLC_8c64_t[8];
typedef double complex SLC_8c128_t[8];
typedef size_t SLC_8size_t[8];
typedef bool SLC_8bool_t[8];
typedef void* SLC_8ptr_t[8];
#pragma endregion
#pragma region sixteen_element_array_type
typedef int8_t SLC_16i8_t[16];
typedef int16_t SLC_16i16_t[16];
typedef int32_t SLC_16i32_t[16];
typedef int64_t SLC_16i64_t[16];
typedef uint8_t SLC_16u8_t[16];
typedef uint16_t SLC_16u16_t[16];
typedef uint32_t SLC_16u32_t[16];
typedef uint64_t SLC_16u64_t[16];
typedef float SLC_16r32_t[16];
typedef double SLC_16r64_t[16];
typedef float complex SLC_16c64_t[16];
typedef double complex SLC_16c128_t[16];
typedef size_t SLC_16size_t[16];
typedef bool SLC_16bool_t[16];
typedef void* SLC_16ptr_t[16];
#pragma endregion

#define SLC_r32_min(__number0, __number1) fminf(__number0, __number1)
#define SLC_r64_min(__number0, __number1) fmin(__number0, __number1)
#define SLC_r32_max(__number0, __number1) fmaxf(__number0, __number1)
#define SLC_r64_max(__number0, __number1) fmax(__number0, __number1)
#define SLC_r32_floor(__number) floorf(__number)
#define SLC_r64_floor(__number) floor(__number)
#define SLC_r32_ceil(__number) ceilf(__number)
#define SLC_r64_ceil(__number) ceil(__number)
#define SLC_r32_abs(__number)  fabsf(__number)
#define SLC_r64_abs(__number)   fabs(__number)
#define SLC_c64_abs(__number)   cabsf(__number)
#define SLC_c128_abs(__number)  cabs(__number)
#define SLC_r32_conj(__number)  (__number)
#define SLC_r64_conj(__number)  (__number)
#define SLC_c64_conj(__number)  conjf(__number)
#define SLC_c128_conj(__number) conj(__number)
#define SLC_r32_fromreal(__number)  (__number)
#define SLC_r64_fromreal(__number)  (__number)
#define SLC_c64_fromreal(__number)  CMPLXF(__number, 0.0f)
#define SLC_c128_fromreal(__number) CMPLX(__number, 0.0f)
#define SLC_r32_print(__out, __delimiter, __number) fprintf(__out, "%s%f", __delimiter, __number)
#define SLC_r64_print(__out, __delimiter, __number) fprintf(__out, "%s%f", __delimiter, __number)
#define SLC_c64_print(__out, __delimiter, __number) fprintf(__out, "%s(%f,%f)", __delimiter, crealf(__number), cimagf(__number))
#define SLC_c128_print(__out, __delimiter, __number) fprintf(__out, "%s(%f,%f)", __delimiter, creal(__number), cimag(__number))
// uniform distribution [-1.0, +1.0] random number generators
#define SLC_r32_rand    ((SLC_r32_t)(rand()-0.5f*RAND_MAX)/(0.5f*RAND_MAX))
#define SLC_r64_rand    ((SLC_r64_t)(rand()-0.5*RAND_MAX)/(0.5*RAND_MAX ))
#define SLC_c64_rand    CMPLXF(SLC_r32_rand, SLC_r32_rand)
#define SLC_c128_rand   CMPLX(SLC_r64_rand, SLC_r64_rand)
// standard tolerances
#define SLC_r32_stdtol  1.0e-5f
#define SLC_r64_stdtol  1.0e-10
#define SLC_c64_stdtol  SLC_r32_stdtol
#define SLC_c128_stdtol SLC_r64_stdtol

#define SLC_product2(__a) (__a)[0]*(__a)[1]
#define SLC_product3(__a) (__a)[0]*(__a)[1]*(__a)[2]
#define SLC_product4(__a) (__a)[0]*(__a)[1]*(__a)[2]*(__a)[3]
#define SLC_product8(__a) (__a)[0]*(__a)[1]*(__a)[2]*(__a)[3]*(__a)[4]*(__a)[5]*(__a)[6]*(__a)[7]

#if !defined(_SLC_NUMBERS_C)
extern SLC_i8_t SLC_i8_units[3]; // { 0, 1, -1 }
extern SLC_i16_t SLC_i16_units[3]; // { 0, 1, -1 }
extern SLC_i32_t SLC_i32_units[3]; // { 0, 1, -1 }
extern SLC_i64_t SLC_i64_units[3]; // { 0, 1, -1 }
extern SLC_u8_t SLC_u8_units[2]; // { 0, 1 }
extern SLC_u16_t SLC_u16_units[2]; // { 0, 1 }
extern SLC_u32_t SLC_u32_units[2]; // { 0, 1 }
extern SLC_u64_t SLC_u64_units[2]; // { 0, 1 }
extern SLC_r32_t SLC_r32_units[3]; // { 0, 1, -1 }
extern SLC_r64_t SLC_r64_units[3]; // { 0, 1, -1 }
extern SLC_c64_t SLC_c64_units[5]; // { 0, (1+0j), (-1+0j), (0+j), (0-j) }
extern SLC_c128_t SLC_c128_units[5]; // { 0, (1+0j), (-1+0j), (0+j), (0-j) }
extern SLC_bool_t SLC_bool_units[2]; // { false, true }
extern SLC_size_t SLC_unitsizes[];
#endif

#define SLC_ALIGN4(__N) ((0 == (__N & 3)) ? __N : ((__N | 3) + 1))

#define SLC_ALIGN8(__N) ((0 == (__N & 7)) ? __N : ((__N | 7) + 1))

#define SLC_ARRAYSIZE(__A)  (sizeof(__A)/sizeof(__A[0]))

#define SLC_COPY2(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1];
#define SLC_COPY3(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; (__DST)[2] = (__SRC)[2];
#define SLC_COPY4(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; \
    (__DST)[2] = (__SRC)[2]; (__DST)[3] = (__SRC)[3];
#define SLC_COPY8(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; \
    (__DST)[2] = (__SRC)[2]; (__DST)[3] = (__SRC)[3]; (__DST)[4] = (__SRC)[4]; (__DST)[5] = (__SRC)[5]; \
    (__DST)[6] = (__SRC)[6]; (__DST)[7] = (__SRC)[7];
#define SLC_COPY16(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; \
    (__DST)[2] = (__SRC)[2]; (__DST)[3] = (__SRC)[3]; (__DST)[4] = (__SRC)[4]; (__DST)[5] = (__SRC)[5]; \
    (__DST)[6] = (__SRC)[6]; (__DST)[7] = (__SRC)[7]; (__DST)[8] = (__SRC)[8]; (__DST)[9] = (__SRC)[9]; \
    (__DST)[10] = (__SRC)[10]; (__DST)[11] = (__SRC)[11]; (__DST)[12] = (__SRC)[12]; (__DST)[13] = (__SRC)[13]; \
    (__DST)[14] = (__SRC)[14]; (__DST)[15] = (__SRC)[15];
#endif