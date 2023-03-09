# Polynomial
## Overview
This group consists of single polynomial and rational of two polynomials.

## Base number types
Polynomial can have four base number types,  
* `SLC_r32_t (float)`  
* `SLC_r64_t (double)`  
* `SLC_c64_t (float complex)`
* `SLC_c128_t (double complex)`

## Dimensions and orders
This group can treat polynomials of 1-D, 2-D, and 3-D.

Table 1. Dimension and order
Dimension | Order | Description
----------|-------|-----------
1 | any | Both of polynomial and rational are supported.
2 | 1 or 2 | linear, bilinear or bicubic interpolation(rational is not supported).
3 | 1 or 2 | linear trilinear or tricubic interpolation(rational is not supported).
<br/>

## Data Types
```
typedef struct {
    SLC_PArray_t numerator;
    SLC_PArray_t denominator;
} SLC_Rational_t, *SLC_PRational_t;
```

## Method
Memory allocation group
```
// 1-D polynomial is represented by SLC_Array_t and it does not have its own allocator.

// 1-D rational allocator
// allocate from heap
SLC_errno_t SLC_Rational_Alloc
(SLC_PRational_t rational, SLC_i16_t numerator_size, SLC_i16_t denominator_size, SLC_i16_t unit_size);
// allocate from stackframe
SLC_errno_t SLC_Rational_Alloca
(SLC_PRational_t rational, SLC_i16_t numerator_size, SLC_i16_t denominator_size, SLC_i16_t unit_size);
```

Polynomial value
```
SLC_<NT>_PolyValue(SLC_PCArray_t coeff, SLC_<NT>_t x);
void SLC_<NT>_Polyvalues(SLC_PCArray_t coeff, SLC_PArray_t values, SLC_PCArray_t x);
```

## Coefficient calculation
Linear interpolation
```
SLC_<NT>_PolyFit1D(SLC_PArray_t coeff, SLC_PCArray_t x, SLC_PCArray_t y);
SLC_<NT>_RationalFit1D(SLC_PRational_t coeff, SLC_PCArray_t x, SLC_PCArray_t y);
```