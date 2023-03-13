#if !defined(_SLC_RINGBUFFER_H)
#define _SLC_RINGBUFFER_H
#include "SLC/SLC_Array.h"
#include "SLC/SLC_errno.h"
#include <errno.h>
#pragma region number_type_agnostic_procesing
#define BUFSIZE(__rb) (__rb)->cont.i16[1]
#define RDINDEX(__rb) (__rb)->cont.i16[2]
#define WRINDEX(__rb) (__rb)->cont.i16[3]

// check if the buffer is full.
bool SLC_RingBuffer_IsFull(SLC_PArray_t rb);

// check if the buffer is empty.
bool SLC_RingBuffer_IsEmpty(SLC_PArray_t rb);

// clear buffer
void SLC_RingBuffer_Clear(SLC_PArray_t rb);

// buffer allocation from heap
SLC_PArray_t SLC_RingBuffer_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size);

// buffer allocation from stackframe
SLC_PArray_t SLC_RingBuffer_Calloca(SLC_i16_t nmemb, SLC_i16_t unit_size);

// get element count existing in the buffer.
int16_t SLC_RingBuffer_AvailableElements(SLC_PArray_t rb);

// get available space in the buffer
int16_t SLC_RingBuffer_AvailableSpace(SLC_PArray_t rb);
#pragma endregion number_type_agnostic_procesing

// put an element.
SLC_errno_t SLC_RingBuffer_Put_i32(SLC_PArray_t rb, const SLC_i32_t* data);

// get an element.
SLC_errno_t SLC_RingBuffer_Get_i32(SLC_PArray_t rb, SLC_i32_t* data);


// put an element.
SLC_errno_t SLC_RingBuffer_Put_u8(SLC_PArray_t rb, const SLC_u8_t* data);

// get an element.
SLC_errno_t SLC_RingBuffer_Get_u8(SLC_PArray_t rb, SLC_u8_t* data);


// put an element.
SLC_errno_t SLC_RingBuffer_Put_u16(SLC_PArray_t rb, const SLC_u16_t* data);

// get an element.
SLC_errno_t SLC_RingBuffer_Get_u16(SLC_PArray_t rb, SLC_u16_t* data);


// put an element.
SLC_errno_t SLC_RingBuffer_Put_ptr(SLC_PArray_t rb, const SLC_ptr_t* data);

// get an element.
SLC_errno_t SLC_RingBuffer_Get_ptr(SLC_PArray_t rb, SLC_ptr_t* data);


#endif
