#if !defined(_SLC_ARRAY_H)
#define _SLC_ARRAY_H
#include "SLC/SLC_Numbers.h"
typedef union {
    SLC_4i16_t i16; // maybe most frequently used
    SLC_i64_t i64;
    SLC_2i32_t i32;
    SLC_8i8_t i8;
    SLC_u64_t u64;
    SLC_2u32_t u32;
    SLC_4u16_t u16;
    SLC_8u8_t u8;
} SLC_ArrayControl_t, *SLC_PArrayControl_t;

typedef union {
    const void* cv;
    SLC_ptr_t ptr;
    SLC_ptr_t* pptr;
    SLC_i8_t* i8;
    SLC_i16_t* i16;
    SLC_i32_t* i32;
    SLC_i64_t* i64;
    SLC_u8_t* u8;
    SLC_u16_t* u16;
    SLC_u32_t* u32;
    SLC_u64_t* u64;
    SLC_r32_t* r32;
    SLC_r64_t* r64;
    SLC_c64_t* c64;
    SLC_c128_t* c128;
    SLC_size_t* s;
    SLC_bool_t* b;
} SLC_ArrayData_t, *SLC_PArrayData_t;

typedef struct {
    SLC_ArrayControl_t cont;
    SLC_ArrayData_t data;
} SLC_Array_t, *SLC_PArray_t;

// giving a unit count and a unit size, get from heap.
SLC_PArray_t SLC_Array_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size);

// giving a unit count and a unit size, get from stack frame.
SLC_PArray_t SLC_Array_Calloca(SLC_i16_t nmemb, SLC_i16_t unit_size);

// giving a multi-dimensional size([0]:unit size, [1]: 1st dimension, [2]: 2nd dimension, [3]: 3rd dimension), get from heap
SLC_PArray_t SLC_Array_Alloc(SLC_4i16_t size);

// giving a multi-dimensional size, get from stack frame.
SLC_PArray_t SLC_Array_Alloca(SLC_4i16_t size);

// return a pointer pointing the element indexed by __ix.
#define SLC_Array_UnitSize(__a) ((__a)->cont.i16[0])
#define SLC_Array_Index1D(__a, __ix) (SLC_Array_UnitSize(__a) * (__ix))
#define SLC_Array_Index2D(__a, __ix, __iy) (SLC_Array_UnitSize(__a) * ((__ix) + (__iy) * (__a)->cont.i16[1]))
#define SLC_Array_Index3D(__a, __ix, __iy, __iz) \
    (SLC_Array_UnitSize(__a) * ((__ix) + (__a)->cont.i16[1] * ((__iy) + (__a)->cont.i16[2] * (__iz) )))
#define SLC_Array_At1D(__a, __T, __ix) (__T)((__a)->data.i8 + SLC_Array_Index1D(__a, __ix))
#define SLC_Array_At2D(__a, __T, __ix, __iy) (__T)((__a)->data.i8 + SLC_Array_Index2D(__a, __ix, __iy))
#define SLC_Array_At3D(__a, __T, __ix, __iy, __iz) (__T)((__a)->data.i8 + SLC_Array_Index3D(__a, __ix, __iy, __iz))
#define SLC_Array_SameSize2D(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[3] == 1) && \
    ((__b)->cont.i16[0] == 1)
#define SLC_Array_TransposedSize2D(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[1])
#define SLC_Array_ValidMatrixProduct(__prod, __left, __right) \
    ((__prod)->cont.i16[0] == (__left)->cont.i16[0]) && \
    ((__prod)->cont.i16[0] == (__right)->cont.i16[0]) && \
    ((__prod)->cont.i16[1] == (__left)->cont.i16[1]) && \
    ((__prod)->cont.i16[2] == (__right)->cont.i16[2]) && \
    ((__left)->cont.i16[2] == (__right)->cont.i16[1])
#define SLC_Array_SameSquareMatrixSize(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[2])
#define SLC_Array_InvWorkSize(__a, __inv) \
    ((__a)->cont.i16[0] == (__inv)->cont.i16[0]) && \
    ((2 * (__a)->cont.i16[1]) == (__inv)->cont.i16[1]) && \
    ((1 + (__a)->cont.i16[2]) == (__inv)->cont.i16[2])
#define SLC_Array_MatRows(__m) (__m)->cont.i16[2]
#define SLC_Array_MatColumns(__m) (__m)->cont.i16[1]
#endif