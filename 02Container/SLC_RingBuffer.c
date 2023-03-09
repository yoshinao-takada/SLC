#include "SLC/SLC_RingBuffer.h"
#pragma region number_type_agnostic_procesing
bool SLC_RingBuffer_IsFull(SLC_PArray_t rb)
{
    SLC_i16_t
        wrindex = WRINDEX(rb),
        rdindex = RDINDEX(rb),
        bufsize = BUFSIZE(rb);
    SLC_i16_t wrindexNext = wrindex + 1;
    if (wrindexNext == bufsize)
    {
        wrindexNext -= bufsize;
    }
    return wrindexNext == rdindex;
}

bool SLC_RingBuffer_IsEmpty(SLC_PArray_t rb)
{
    return WRINDEX(rb) == RDINDEX(rb);
}

void SLC_RingBuffer_Clear(SLC_PArray_t rb)
{
    rb->cont.i16[2] = rb->cont.i16[3] = 0;
}

SLC_PArray_t SLC_RingBuffer_Calloc(SLC_i16_t nmemb, SLC_i16_t unit_size)
{
    SLC_PArray_t p = SLC_Array_Calloc(nmemb, unit_size);
    SLC_RingBuffer_Clear(p);
    return p;
}

SLC_PArray_t SLC_RingBuffer_Calloca(SLC_i16_t nmemb, SLC_i16_t unit_size)
{
    SLC_PArray_t p = SLC_Array_Calloca(nmemb, unit_size);
    SLC_RingBuffer_Clear(p);
    return p;
}

int16_t SLC_RingBuffer_AvailableElements(SLC_PArray_t rb)
{
    int16_t wrindex = WRINDEX(rb), rdindex = RDINDEX(rb);
    if (wrindex < rdindex)
    {
        wrindex += BUFSIZE(rb);
    }
    return wrindex - rdindex;
}

int16_t SLC_RingBuffer_AvailableSpace(SLC_PArray_t rb)
{
    int16_t wrindex = WRINDEX(rb), rdindex = RDINDEX(rb);
    if (rdindex > wrindex)
    {
        rdindex -= BUFSIZE(rb);
    }
    return wrindex - rdindex - 1;
}
#pragma endregion number_type_agnostic_procesing
SLC_errno_t SLC_RingBuffer_Put_i32(SLC_PArray_t rb, const SLC_i32_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_i32_t* buf;
    int16_t wrindex, bufsize;
    do {
        if (SLC_RingBuffer_IsFull(rb))
        {
            err = ENOBUFS;
            break;
        }
        buf = rb->data.i32;
        wrindex = WRINDEX(rb), bufsize = BUFSIZE(rb);
        buf[wrindex++] = *data;
        if (wrindex == bufsize)
        {
            wrindex -= bufsize;
        }
        BUFSIZE(rb) = wrindex;
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Get_i32(SLC_PArray_t rb, SLC_i32_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_i32_t* buf;
    int16_t rdindex, bufsize;
    do {
        if (SLC_RingBuffer_IsEmpty(rb))
        {
            err = ENODATA;
            break;
        }
        buf = rb->data.i32;
        rdindex = RDINDEX(rb), bufsize = BUFSIZE(rb);
        *data = buf[rdindex++];
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Put_u8(SLC_PArray_t rb, const SLC_u8_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_u8_t* buf;
    int16_t wrindex, bufsize;
    do {
        if (SLC_RingBuffer_IsFull(rb))
        {
            err = ENOBUFS;
            break;
        }
        buf = rb->data.u8;
        wrindex = WRINDEX(rb), bufsize = BUFSIZE(rb);
        buf[wrindex++] = *data;
        if (wrindex == bufsize)
        {
            wrindex -= bufsize;
        }
        BUFSIZE(rb) = wrindex;
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Get_u8(SLC_PArray_t rb, SLC_u8_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_u8_t* buf;
    int16_t rdindex, bufsize;
    do {
        if (SLC_RingBuffer_IsEmpty(rb))
        {
            err = ENODATA;
            break;
        }
        buf = rb->data.u8;
        rdindex = RDINDEX(rb), bufsize = BUFSIZE(rb);
        *data = buf[rdindex++];
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Put_u16(SLC_PArray_t rb, const SLC_u16_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_u16_t* buf;
    int16_t wrindex, bufsize;
    do {
        if (SLC_RingBuffer_IsFull(rb))
        {
            err = ENOBUFS;
            break;
        }
        buf = rb->data.u16;
        wrindex = WRINDEX(rb), bufsize = BUFSIZE(rb);
        buf[wrindex++] = *data;
        if (wrindex == bufsize)
        {
            wrindex -= bufsize;
        }
        BUFSIZE(rb) = wrindex;
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Get_u16(SLC_PArray_t rb, SLC_u16_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_u16_t* buf;
    int16_t rdindex, bufsize;
    do {
        if (SLC_RingBuffer_IsEmpty(rb))
        {
            err = ENODATA;
            break;
        }
        buf = rb->data.u16;
        rdindex = RDINDEX(rb), bufsize = BUFSIZE(rb);
        *data = buf[rdindex++];
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Put_ptr(SLC_PArray_t rb, const SLC_ptr_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_ptr_t* buf;
    int16_t wrindex, bufsize;
    do {
        if (SLC_RingBuffer_IsFull(rb))
        {
            err = ENOBUFS;
            break;
        }
        buf = rb->data.ptr;
        wrindex = WRINDEX(rb), bufsize = BUFSIZE(rb);
        buf[wrindex++] = *data;
        if (wrindex == bufsize)
        {
            wrindex -= bufsize;
        }
        BUFSIZE(rb) = wrindex;
    } while (0);
    return err;
}

SLC_errno_t SLC_RingBuffer_Get_ptr(SLC_PArray_t rb, SLC_ptr_t* data)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_ptr_t* buf;
    int16_t rdindex, bufsize;
    do {
        if (SLC_RingBuffer_IsEmpty(rb))
        {
            err = ENODATA;
            break;
        }
        buf = rb->data.ptr;
        rdindex = RDINDEX(rb), bufsize = BUFSIZE(rb);
        *data = buf[rdindex++];
    } while (0);
    return err;
}

