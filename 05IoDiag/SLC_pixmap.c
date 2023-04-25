#include "SLC/SLC_pixmap.h"
#include <stdlib.h>
#include <assert.h>

const SLC_i16_t* SLC_pixmap_Size4u8(SLC_4i16_t size, SLC_i16_t width, SLC_i16_t height)
{
    size[0] = 4;
    size[1] = width;
    size[2] = height;
    size[3] = 1;
}

const SLC_i16_t* SLC_pixmap_Size4i16(SLC_4i16_t size, SLC_i16_t width, SLC_i16_t height)
{
    size[0] = 8;
    size[1] = width;
    size[2] = height;
    size[3] = 1;
}

const SLC_i16_t* SLC_pixmap_Size4r32(SLC_4i16_t size, SLC_i16_t width, SLC_i16_t height)
{
    size[0] = 16;
    size[1] = width;
    size[2] = height;
    size[3] = 1;
}

SLC_errno_t SLC_pixmap_Line4u8(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t closed,
    SLC_4u8_t value
) {
    SLC_errno_t err = EXIT_SUCCESS;
    assert((closed && (polyline->cont.i16[2] >= 3)) ||
        (!closed && (polyline->cont.i16[2] >= 2)));
    do {
        const SLC_i16_t cornerIndexLimit = closed ? 
            polyline->cont.i16[2] + 1 : polyline->cont.i16[2];
        for (SLC_i16_t i = 0; i < cornerIndexLimit; i++)
        {
            const SLC_i16_t cornerIndex = (i >= polyline->cont.i16[2]) ?
                 i - polyline->cont.i16[2] : i;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_pixmap_Line4i16(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t closed,
    SLC_4u8_t value
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

SLC_errno_t SLC_pixmap_Line4r32(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t closed,
    SLC_4u8_t value
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

SLC_errno_t SLC_pixmap_Fill4u8(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t fillOuter,
    SLC_4u8_t value
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

SLC_errno_t SLC_pixmap_Fill4i16(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t fillOuter,
    SLC_4u8_t value
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

SLC_errno_t SLC_pixmap_Fill4r32(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t fillOuter,
    SLC_4u8_t value
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}
