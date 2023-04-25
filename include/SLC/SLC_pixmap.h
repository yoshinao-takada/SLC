#if !defined(SLC_PIXMAP_H)
#define SLC_PIXMAP_H
#include "SLC/SLC_Array.h"
#include "SLC/SLC_errno.h"

/*!
\brief set array size of a pixelmap of B8G8R8A8 or R8G8B8A8.
\param size [out] is fed to SLC_Array_Alloc or SLC_Array_Alloca
\param width [in] is the width of the pixelmap to create.
\apram height [in] is the height of the pixelmap to create.
*/
const SLC_i16_t* SLC_pixmap_Size4u8(SLC_4i16_t size, SLC_i16_t width, SLC_i16_t height);
#define SLC_pixmap_NewSize4u8(__width, __height) SLC_pixmap_Size4u8( \
    (SLC_i16_t*)alloca(8), __width, __height)

/*!
\brief set array size of pixelmap of B16G16R16A16 or R16G16B16A16
\param size [out] is fed to SLC_Array_Alloc or SLC_Array_Alloca
\param width [in] is the width of the pixelmap to create.
\apram height [in] is the height of the pixelmap to create.
*/
const SLC_i16_t* SLC_pixmap_Size4i16(SLC_4i16_t size, SLC_i16_t width, SLC_i16_t height);
#define SLC_pixmap_NewSize4i16(__width, __height) SLC_pixmap_Size4i16( \
    (SLC_i16_t*)alloca(8), __width, __height)

/*!
\brief set array size of pixelmap of B32G32R32A32 or R32G32B32A32
\param size [out] is fed to SLC_Array_Alloc or SLC_Array_Alloca
\param width [in] is the width of the pixelmap to create.
\apram height [in] is the height of the pixelmap to create.
*/
const SLC_i16_t* SLC_pixmap_Size4r32(SLC_4i16_t size, SLC_i16_t width, SLC_i16_t height);
#define SLC_pixmap_NewSize4r32(__width, __height) SLC_pixmap_Size4r32( \
    (SLC_i16_t*)alloca(8), __width, __height)

#define SLC_pixmap_Pixel4u8(__pixmap, __ix, __iy) \
(SLC_u8_t*)( \
    __pixmap->data._u8 + \
    __pixmap->cont.i16[0] * (__ix + iy * __pixmap->cont.i16[1]))

#define SLC_pixmap_CPixel4u8(__pixmap, __ix, __iy) \
(const SLC_u8_t*)( \
    __pixmap->data._u8 + \
    __pixmap->cont.i16[0] * (__ix + iy * __pixmap->cont.i16[1]))

#define SLC_pixmap_Pixel4i16(__pixmap, __ix, __iy) \
(SLC_i16_t*)( \
    __pixmap->data._u8 + \
    __pixmap->cont.i16[0] * (__ix + iy * __pixmap->cont.i16[1]))

#define SLC_pixmap_CPixel4i16(__pixmap, __ix, __iy) \
(const SLC_i16_t*)( \
    __pixmap->data._u8 + \
    __pixmap->cont.i16[0] * (__ix + iy * __pixmap->cont.i16[1]))

#define SLC_pixmap_Pixel4r32(__pixmap, __ix, __iy) \
(SLC_r32_t*)( \
    __pixmap->data._u8 + \
    __pixmap->cont.i16[0] * (__ix + iy * __pixmap->cont.i16[1]))

#define SLC_pixmap_CPixel4r32(__pixmap, __ix, __iy) \
(const SLC_r32_t*)( \
    __pixmap->data._u8 + \
    __pixmap->cont.i16[0] * (__ix + iy * __pixmap->cont.i16[1]))

#define SLC_pixmap_Set4u8(__pixmap, __ix, __iy, value) \
    *(SLC_u32_t*)SLC_pixmap_Pixel4u8(__pixmap, __ix, __iy) = *(const SLC_u32_t*)(value)

#define SLC_pixmap_Set4i16(__pixmap, __ix, __iy, value) \
    *(SCL_u64_t*)SLC_pixmap_Pixel4i16(__pixmap, __ix, __iy) = *(const SLC_u64*)(value)

#define SLC_pixmap_Set4r32(__pixmap, __ix, __iy, value) \
    SLC_COPY4(SLC_pixmap_Pixel4r32(__pixmap, __ix, __iy), value)

/*!
\brief draw a line
\param pixmap [in,out]
\param polyline [in] contains two or more pixel coordinates represented in SLC_r32_t.
\param closed [in] true means that the polyline forms a crosed shape.
\param value [in] is a pixel color.
*/
SLC_errno_t SLC_pixmap_Line4u8(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t closed,
    SLC_4u8_t value);

SLC_errno_t SLC_pixmap_Line4i16(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t closed,
    SLC_4u8_t value);

SLC_errno_t SLC_pixmap_Line4r32(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t closed,
    SLC_4u8_t value);


/*!
\brief fill in a polygon
\param pixmap [in,out]
\param polyline [in] contains three or more pixel coordinates represented in SLC_r32_t.
    It must form a polygon.
\param fillOuter [in] if true, fill outside the polygon.
\param value [in] is a pixel color.
*/
SLC_errno_t SLC_pixmap_Fill4u8(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t fillOuter,
    SLC_4u8_t value);

SLC_errno_t SLC_pixmap_Fill4i16(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t fillOuter,
    SLC_4u8_t value);

SLC_errno_t SLC_pixmap_Fill4r32(
    SLC_PArray_t pixmap,
    SLC_PArray_t polyline,
    SLC_bool_t fillOuter,
    SLC_4u8_t value);

#endif