# 1-D, 2-D, and 3-D array object
The base container is defined as
```
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
    SLC_c128* c128;
    SLC_size_t* s;
    SLC_bool_t* b;
} SLC_ArrayData_t, *SLC_PArrayData_t;

typedef struct {
    SLC_ArrayControl_t cont;
    SLC_ArrayData_t data;
} SLC_Array_t, *SLC_PArray_t;

```
Generic allocation methods are
```
// giving a unit count and a unit size, get from heap.
SLC_PArray_t SLC_Array_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size);

// giving a unit count and a unit size, get from stack frame.
SLC_PArray_t SLC_Array_Calloca(SLC_i16_t nmemb, SLC_i16_t unit_size);

// giving a multi-dimensional size([0]:unit size, [1]: 1st dimension, [2]: 2nd dimension, [3]: 3rd dimension), get from heap
SLC_PArray_t SLC_Array_Alloc(SLC_4i16_t size);

// giving a multi-dimensional size, get from stack frame.
SLC_PArray_t SLC_Array_Alloca(SLC_4i16_t size);
```
