#include "SLC/SLC_Polyline.h"
#pragma region SLC_Polyliner32_Utility_Functions
#pragma region Dimension_Agnostic_Utility_Functions

// find a node with the minimum x coordinate
SLC_i16_t SLC_Polyliner32_MinX(SLC_PCArray_t polyline)
{
    const SLC_r32_t* px = polyline->data._r32;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (px[4 * found] > px[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the minimum y coordinate
SLC_i16_t SLC_Polyliner32_MinY(SLC_PCArray_t polyline)
{
    const SLC_r32_t* py = polyline->data._r32 + 1;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (py[4 * found] > py[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the minimum z coordinate
SLC_i16_t SLC_Polyliner32_MinZ(SLC_PCArray_t polyline)
{
    const SLC_r32_t* pz = polyline->data._r32 + 2;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (pz[4 * found] > pz[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the maximum x coordinate
SLC_i16_t SLC_Polyliner32_MaxX(SLC_PCArray_t polyline)
{
    const SLC_r32_t* px = polyline->data._r32;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (px[4 * found] < px[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the maximum y coordinate
SLC_i16_t SLC_Polyliner32_MaxY(SLC_PCArray_t polyline)
{
    const SLC_r32_t* py = polyline->data._r32 + 1;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (py[4 * found] < py[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the maximum z coordinate
SLC_i16_t SLC_Polyliner32_MaxZ(SLC_PCArray_t polyline)
{
    const SLC_r32_t* pz = polyline->data._r32 + 2;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (pz[4 * found] < pz[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// extract coordinates of the two ends of a segment selected by index.
void SLC_Polyliner32_Segment(SLC_PCArray_t polyline, SLC_i16_t index,
    SLC_PPolylineSegmentr32_t segment
) {
    segment->node0 = polyline->data._r32 + 4 * index;
    if (++index == polyline->cont.i16[2]) index = 0;
    segment->node0 = polyline->data._r32 + 4 * index;
}
#pragma endregion Dimension_Agnostic_Utility_Functions
#pragma region 2D_Utility_Functions
void SLC_Segmentr32_ApproxPixelsLandscape(
    SLC_PArray_t uvw, const SLC_2i16_t urange, SLC_PCLinePlaner32_t segProp, SLC_i16_t radius
) {
    SLC_i16_t* pixel = uvw->data._i16;
    const SLC_i16_t dimension = uvw->cont.i16[1];
    const SLC_i16_t vertical_pixels = radius + radius + 1;
    const SLC_i16_t du = (urange[1] > urange[0]) ? 1 : -1;
    SLC_i16_t u = urange[0];
    SLC_r32_t dvdu = segProp->v0[1] / segProp->v0[0];
    do {
        SLC_r32_t vcenter = segProp->p0[1] + dvdu * (u - urange[0]);
        for (SLC_i16_t voffset = -radius; voffset <= radius; voffset++)
        {
            SLC_i16_t v = (SLC_i16_t)(vcenter + voffset);
            pixel[0] = u;
            pixel[1] = v;
            pixel[2] = 0;
            pixel += dimension;
        }
        u += du;
    } while (u != urange[1]);
}

void SLC_Segmentr32_ApproxPixelsPortrait(
    SLC_PArray_t uvw, const SLC_2i16_t vrange, SLC_PCLinePlaner32_t segProp, SLC_i16_t radius
) {
    SLC_i16_t* pixel = uvw->data._i16;
    const SLC_i16_t dimension = uvw->cont.i16[1];
    const SLC_i16_t horizontal_pixels = radius + radius + 1;
    const SLC_i16_t dv = (vrange[1] > vrange[0]) ? 1 : -1;
    SLC_i16_t v = vrange[0];
    SLC_r32_t dudv = segProp->v0[0] / segProp->v0[1];
    do {
        SLC_r32_t ucenter = segProp->p0[0] + dudv * (v - vrange[0]);
        for (SLC_i16_t uoffset = -radius; uoffset <= radius; uoffset++)
        {
            SLC_i16_t u = (SLC_i16_t)(ucenter + uoffset);
            pixel[0] = u;
            pixel[1] = v;
            pixel[2] = 0;
            pixel += dimension;
        }
        v += dv;
    } while (v != vrange[1]);
}

// create an array of pixels in the approximated vicinity
SLC_errno_t SLC_Segmentr32_ApproxPixels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuvw
) {
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r32_t xdistance = SLC_r32_abs(segment->node0[0] - segment->node1[0]);
    SLC_r32_t ydistance = SLC_r32_abs(segment->node0[1] - segment->node1[1]);
    SLC_LinePlaner32_t segProp;
    SLC_i16_t nLongEdge, nShortEdge = 1 + 2 * approxRadius;
    do {
        if (xdistance > ydistance)
        { // landscape like layout
        }
        else
        { // portrait like layout
        }
    } while (0);
    return err;
}

// create an array of pixels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr32_NearbyPixels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuvw
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        
    } while (0);
    return err;
}
#pragma endregion 2D_Utility_Functions
#pragma region 3D_Utility_Functions
// create an array of voxels in the approximated vicinity
SLC_errno_t SLC_Segmentr32_ApproxVoxels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuvw);

// check if a 3D voxel index uvw is on the line segment.
void SLC_Segmentr32_IsOn2D(SLC_PCPolylineSegmentr32_t segment,
    SLC_PCArray_t uvw, SLC_r32_t vicinityRadius, SLC_PArray_t isOn);

// create an array of voxels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr32_NearbyVoxels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuvw);
#pragma endregion 3D_Utility_Functions
#pragma endregion SLC_Polyliner32_Utility_Functions
#pragma region SLC_Polyliner64_Utility_Functions
#pragma region Dimension_Agnostic_Utility_Functions

// find a node with the minimum x coordinate
SLC_i16_t SLC_Polyliner64_MinX(SLC_PCArray_t polyline)
{
    const SLC_r64_t* px = polyline->data._r64;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (px[4 * found] > px[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the minimum y coordinate
SLC_i16_t SLC_Polyliner64_MinY(SLC_PCArray_t polyline)
{
    const SLC_r64_t* py = polyline->data._r64 + 1;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (py[4 * found] > py[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the minimum z coordinate
SLC_i16_t SLC_Polyliner64_MinZ(SLC_PCArray_t polyline)
{
    const SLC_r64_t* pz = polyline->data._r64 + 2;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (pz[4 * found] > pz[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the maximum x coordinate
SLC_i16_t SLC_Polyliner64_MaxX(SLC_PCArray_t polyline)
{
    const SLC_r64_t* px = polyline->data._r64;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (px[4 * found] < px[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the maximum y coordinate
SLC_i16_t SLC_Polyliner64_MaxY(SLC_PCArray_t polyline)
{
    const SLC_r64_t* py = polyline->data._r64 + 1;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (py[4 * found] < py[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// find a node with the maximum z coordinate
SLC_i16_t SLC_Polyliner64_MaxZ(SLC_PCArray_t polyline)
{
    const SLC_r64_t* pz = polyline->data._r64 + 2;
    SLC_i16_t found = 0;
    for (SLC_i16_t i = 1; i < polyline->cont.i16[2]; i++)
    {
        if (pz[4 * found] < pz[4 * i])
        {
            found = i;
        }
    }
    return found;
}

// extract coordinates of the two ends of a segment selected by index.
void SLC_Polyliner64_Segment(SLC_PCArray_t polyline, SLC_i16_t index,
    SLC_PPolylineSegmentr64_t segment
) {
    segment->node0 = polyline->data._r64 + 4 * index;
    if (++index == polyline->cont.i16[2]) index = 0;
    segment->node0 = polyline->data._r64 + 4 * index;
}
#pragma endregion Dimension_Agnostic_Utility_Functions
#pragma region 2D_Utility_Functions
void SLC_Segmentr64_ApproxPixelsLandscape(
    SLC_PArray_t uvw, const SLC_2i16_t urange, SLC_PCLinePlaner64_t segProp, SLC_i16_t radius
) {
    SLC_i16_t* pixel = uvw->data._i16;
    const SLC_i16_t dimension = uvw->cont.i16[1];
    const SLC_i16_t vertical_pixels = radius + radius + 1;
    const SLC_i16_t du = (urange[1] > urange[0]) ? 1 : -1;
    SLC_i16_t u = urange[0];
    SLC_r64_t dvdu = segProp->v0[1] / segProp->v0[0];
    do {
        SLC_r64_t vcenter = segProp->p0[1] + dvdu * (u - urange[0]);
        for (SLC_i16_t voffset = -radius; voffset <= radius; voffset++)
        {
            SLC_i16_t v = (SLC_i16_t)(vcenter + voffset);
            pixel[0] = u;
            pixel[1] = v;
            pixel[2] = 0;
            pixel += dimension;
        }
        u += du;
    } while (u != urange[1]);
}

void SLC_Segmentr64_ApproxPixelsPortrait(
    SLC_PArray_t uvw, const SLC_2i16_t vrange, SLC_PCLinePlaner64_t segProp, SLC_i16_t radius
) {
    SLC_i16_t* pixel = uvw->data._i16;
    const SLC_i16_t dimension = uvw->cont.i16[1];
    const SLC_i16_t horizontal_pixels = radius + radius + 1;
    const SLC_i16_t dv = (vrange[1] > vrange[0]) ? 1 : -1;
    SLC_i16_t v = vrange[0];
    SLC_r64_t dudv = segProp->v0[0] / segProp->v0[1];
    do {
        SLC_r64_t ucenter = segProp->p0[0] + dudv * (v - vrange[0]);
        for (SLC_i16_t uoffset = -radius; uoffset <= radius; uoffset++)
        {
            SLC_i16_t u = (SLC_i16_t)(ucenter + uoffset);
            pixel[0] = u;
            pixel[1] = v;
            pixel[2] = 0;
            pixel += dimension;
        }
        v += dv;
    } while (v != vrange[1]);
}

// create an array of pixels in the approximated vicinity
SLC_errno_t SLC_Segmentr64_ApproxPixels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuvw
) {
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_r64_t xdistance = SLC_r64_abs(segment->node0[0] - segment->node1[0]);
    SLC_r64_t ydistance = SLC_r64_abs(segment->node0[1] - segment->node1[1]);
    SLC_LinePlaner64_t segProp;
    SLC_i16_t nLongEdge, nShortEdge = 1 + 2 * approxRadius;
    do {
        if (xdistance > ydistance)
        { // landscape like layout
        }
        else
        { // portrait like layout
        }
    } while (0);
    return err;
}

// create an array of pixels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr64_NearbyPixels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuvw
) {
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        
    } while (0);
    return err;
}
#pragma endregion 2D_Utility_Functions
#pragma region 3D_Utility_Functions
// create an array of voxels in the approximated vicinity
SLC_errno_t SLC_Segmentr64_ApproxVoxels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuvw);

// check if a 3D voxel index uvw is on the line segment.
void SLC_Segmentr64_IsOn2D(SLC_PCPolylineSegmentr64_t segment,
    SLC_PCArray_t uvw, SLC_r64_t vicinityRadius, SLC_PArray_t isOn);

// create an array of voxels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr64_NearbyVoxels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuvw);
#pragma endregion 3D_Utility_Functions
#pragma endregion SLC_Polyliner64_Utility_Functions
