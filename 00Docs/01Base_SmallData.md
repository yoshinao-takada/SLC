 # Small Data Structures
 ## Overview
This group contains subgroups listed in Table 1.  
<br/>
Table 1. Library subgroups  
Name      | Description
----------|------------------
`SLC_Numbers` | 1) Type redifinitions of `stdint`, floating number types, and complex number types.<br/>2) small fixed size vectors of the number types in 1), <br/>3) enumeration and sizes of 1) and 2).
`SLC_NumberCopy` | 1-by-1 copy, swap, and scatter gather of types of 1) in `SLC_Numbers`.

<br/>

## Base number types
Table 2. Base number types
Name | std-C built-in type or `stdint` type | enumeration
-----|---------------------|---
`SLC_i8_t` | `int8_t` | `SLC_i8`
`SLC_i16_t` | `int16_t` | `SLC_i16`
`SLC_i32_t` | `int32_t` | `SLC_i32`
`SLC_i64_t` | `int64_t` | `SLC_i64`
`SLC_u8_t` | `uint8_t` | `SLC_u8`
`SLC_u16_t` | `uint16_t` | `SLC_u16`
`SLC_u32_t` | `uint32_t` | `SLC_u32`
`SLC_u64_t` | `uint64_t` | `SLC_u64`
`SLC_r32_t` | `float`    | `SLC_r32`
`SLC_r64_t` | `double`   | `SCL_r64`
`SLC_c64_t` | `float complex` | `SLC_c64`
`SLC_c128_t` | `double complex` | `SLC_c128`
`SLC_size_t` | `size_t`  | `SLC_size`
`SLC_bool_t` | `bool` | `SLC_bool`
`SLC_ptr_t` | `void*` | `SLC_ptr`
<br/>

## Small fixed size arrays
Table 3. Small fixed size arrays
Name | Base number type | Array size
-----|------------------|-----------
`SLC_2i8_t` | `SLC_i8_t | 2
`SLC_3i8_t` | `SLC_i8_t | 3
`SLC_4i8_t` | `SLC_i8_t | 4
`SLC_8i8_t` | `SLC_i8_t | 8
`SLC_16i8_t` | `SLC_i8_t | 16
<br/>

Other base number types also have their array types of size 2, 3, and 4.
Arithmetic macro `SLC_product<N>` are defined as
```
#define SLC_product2(__a) ((__a)[0] * (__a)[1])
#define SLC_product3(__a) ((__a)[0] * (__a)[1] * (__a)[2])
#define SLC_product4(__a) ((__a)[0] * (__a)[1] * (__a)[2] * (__a)[3])
```

## Array copy functions
For example for `SLC_i64_t`,
```
void SLC_i64_copy(
    SLC_i64_t* dst, SLC_size_t dst_step,
    const SLC_i64_t* src, SLC_size_t src_step,
    SLC_size_t count);
```


## Unit elements and Zeros
Macros representing unit elements and zeros of the base number types are defined.
And global variables of two element arrays. The first element is zero and the second element is 
the unit element.  
For example for `SLC_u32_t`,
```
extern SLC_2u32_t SLC_2u32_01;
SLC_2u32_t SLC_2u32_01 = { 0, 1 };
```
