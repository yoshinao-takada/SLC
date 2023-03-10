#include "SLC/SLC_Array.h"
#include <stdlib.h>
#include <alloca.h>

static SLC_PArray_t SLC_Array_InitHeader(void* ptr, SLC_i16_t nmemb, SLC_i16_t unit_size)
{
    SLC_PArray_t pa = (SLC_PArray_t)ptr;
    pa->cont.i16[0] = unit_size;
    pa->cont.i16[1] = nmemb;
    pa->cont.i16[2] = pa->cont.i16[3] = 1;
    pa->data.cv = (const void*)(pa + 1);
    return pa;
}

SLC_PArray_t SLC_Array_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size)
{
    size_t alloc_size = nmemb * unit_size + sizeof(SLC_Array_t);
    void* ptr = aligned_alloc(8, alloc_size);
    return SLC_Array_InitHeader(ptr, nmemb, unit_size);
}

SLC_PArray_t SLC_Array_Calloca(SLC_i16_t nmemb, SLC_i16_t unit_size)
{
    size_t total_bytes = nmemb * unit_size + sizeof(SLC_Array_t);
    size_t alloc_size = SLC_ALIGN8(total_bytes);
    void* ptr = alloca(alloc_size);
    return SLC_Array_InitHeader(ptr, nmemb, unit_size);
}

static SLC_PArray_t SLC_Array_InitHeader2(void* ptr, SLC_4i16_t size)
{
    SLC_PArray_t pa = (SLC_PArray_t)ptr;
    SLC_COPY4(pa->cont.i16, size);
    pa->data.cv = (const void*)(pa + 1);
    return pa;
}

SLC_PArray_t SLC_Array_Alloc(SLC_4i16_t size)
{
    size_t alloc_size = SLC_product4(size) + sizeof(SLC_Array_t);
    void* ptr = aligned_alloc(8, alloc_size);
    return SLC_Array_InitHeader2(ptr, size);
}

SLC_PArray_t SLC_Array_Alloca(SLC_4i16_t size)
{
    size_t total_bytes = SLC_product4(size) + sizeof(SLC_Array_t);
    size_t alloc_size = SLC_ALIGN8(total_bytes);
    void* ptr = alloca(alloc_size);
    return SLC_Array_InitHeader2(ptr, size);
}
