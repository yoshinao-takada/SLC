# Ring Buffer
## Overview
Ring buffer can be implemented using `SLC_Array_t`. `SLC_ArrayControl_t` is used in a manner different
from `SLC_Array_t`.
* Union member `i16` is used.
* i16[0] is used as a unit size. It is identical to `SLC_Array_t`.
* i16[1] is used as a buffer size. It is same as 1-D array of `SLC_Array_t`.
* i16[2] is used as a read indexer.
* i16[3] is used as a write indexer.

Buffer allocation is done by the methods below.

```
// giving a unit count and a unit size, get from heap.
SLC_PArray_t SLC_RingBuffer_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size);

// giving a unit count and a unit size, get from stack frame.
SLC_PArray_t SLC_RingBuffer_Calloca(SLC_i16_t nmemb, SLC_i16_t unit_size);
```
Reseting a read indexer and a write indexer, a method is supplied as
```
void SLC_RingBuffer_Reset(SLC_PArray_t ringbuffer);
```

Ring buffer supports the element types in table 1 as default,  
<br/>Table 1. Supported element types
Element type | Typical use case
-------------|--------------------
SLC_u8_t     | ASCII or UTF-8 character buffer
SLC_u16_t    | UTF-16 character buffer
SLC_i32_t    | Generic integer buffer
SLC_ptr_t    | Generic variable sized data buffer
<br/>

## Methods
```
typedef enum {
    SLC_RingBuffer_Error_Full = 0x1000,
    SLC_RingBuffer_Error_Empty,
} SLC_RingBuffer_Error_t;

// put an element.
SLC_errno_t SLC_RingBuffer_Put_<TypeID>(SLC_PArray_t rb, T data);

// get an element.
SLC_errno_t SLC_RingBuffer_Get_<TypeID>(SLC_PArray_t rb, T* data);

// put elements.
SLC_errno_t SLC_RingBuffer_Puts_<TypeID>(SLC_PArray_t rb, const T* data);

// get elements.
SLC_errno_t SLC_RingBuffer_Gets_<TypeID>(SLC_PArray_t rb, T* data);

// count available elements.
SLC_i16_t SLC_RingBuffer_Count(SLC_PArray_t rb);

// count available space.
SLC_i16_t SLC_RingBuffer_CountSpace(SLC_PArray_t rb);
```