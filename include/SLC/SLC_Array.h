#if !defined(_SLC_ARRAY_H)
#define _SLC_ARRAY_H
#include "SLC/SLC_Numbers.h"
typedef union {
    SLC_4i16_t i16; // maybe this is the most frequently used configuration.
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
    SLC_ptr_t _ptr; // void*
    SLC_ptr_t* _pptr; // void**
    SLC_i8_t* _i8;
    SLC_i16_t* _i16;
    SLC_i32_t* _i32;
    SLC_i64_t* _i64;
    SLC_u8_t* _u8;
    SLC_u16_t* _u16;
    SLC_u32_t* _u32;
    SLC_u64_t* _u64;
    SLC_r32_t* _r32;
    SLC_r64_t* _r64;
    SLC_c64_t* _c64;
    SLC_c128_t* _c128;
    SLC_size_t* _size;
    SLC_bool_t* _bool;
} SLC_ArrayData_t, *SLC_PArrayData_t;

typedef struct {
    SLC_ArrayControl_t cont;
    SLC_ArrayData_t data;
} SLC_Array_t, *SLC_PArray_t;

SLC_PArray_t SLC_Array_InitHeader(void* ptr, SLC_i16_t nmemb, SLC_i16_t unit_size);
SLC_PArray_t SLC_Array_InitHeader2(void* ptr, const SLC_4i16_t size);

// giving a unit count and a unit size, get from heap.
SLC_PArray_t SLC_Array_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size);

// giving a unit count and a unit size, get from stack frame.
#define SLC_Array_Calloca(__nmemb, __unit_size) SLC_Array_InitHeader( \
    alloca(SLC_ALIGN8(__nmemb * __unit_size + sizeof(SLC_Array_t))), __nmemb, __unit_size)

// giving a multi-dimensional size([0]:unit size, [1]: 1st dimension, [2]: 2nd dimension, [3]: 3rd dimension), get from heap
SLC_PArray_t SLC_Array_Alloc(const SLC_4i16_t size);

// giving a multi-dimensional size, get from stack frame.
#define SLC_Array_Alloca(__size) SLC_Array_InitHeader2( \
    alloca(SLC_ALIGN8(SLC_product4(__size) + sizeof(SLC_Array_t))), __size)

// return a pointer pointing the element indexed by __ix.
#define SLC_Array_UnitSize(__a) ((__a)->cont.i16[0])
#define SLC_Array_Index1D(__a, __ix) (SLC_Array_UnitSize(__a) * (__ix))
#define SLC_Array_Index2D(__a, __ix, __iy) (SLC_Array_UnitSize(__a) * ((__ix) + (__iy) * (__a)->cont.i16[1]))
#define SLC_Array_Index3D(__a, __ix, __iy, __iz) \
    (SLC_Array_UnitSize(__a) * ((__ix) + (__a)->cont.i16[1] * ((__iy) + (__a)->cont.i16[2] * (__iz) )))
#define SLC_Array_At1D(__a, __T, __ix) (__T)((__a)->data._i8 + SLC_Array_Index1D(__a, __ix))
#define SLC_Array_At2D(__a, __T, __ix, __iy) (__T)((__a)->data._i8 + SLC_Array_Index2D(__a, __ix, __iy))
#define SLC_Array_At3D(__a, __T, __ix, __iy, __iz) (__T)((__a)->data._i8 + SLC_Array_Index3D(__a, __ix, __iy, __iz))
#define SLC_Array_SameSize2D(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[3] == 1) && \
    ((__b)->cont.i16[3] == 1)
#define SLC_Array_TransposedSize2D(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[3] == 1) && \
    ((__b)->cont.i16[3] == 1)
#define SLC_Array_ValidMatrixProduct(__prod, __left, __right) \
    ((__prod)->cont.i16[0] == (__left)->cont.i16[0]) && \
    ((__prod)->cont.i16[0] == (__right)->cont.i16[0]) && \
    ((__prod)->cont.i16[2] == (__left)->cont.i16[2]) && \
    ((__prod)->cont.i16[1] == (__right)->cont.i16[1]) && \
    ((__left)->cont.i16[1] == (__right)->cont.i16[2]) && \
    ((__left)->cont.i16[3] == 1) && \
    ((__right)->cont.i16[3] == 1) && \
    ((__prod)->cont.i16[3] == 1)
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
#define SLC_TransposedMatSize(__matsize) { __matsize[0], __matsize[2], __matsize[1], 1 }
#define SLC_InvMatWorkSize(__matsize) { __matsize[0], 2 * __matsize[1], 1 + __matsize[2], 1 }
#endif