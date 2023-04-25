#if !defined(_SLC_Polyline_H)
#define _SLC_Polyline_H
#include "SLC/SLC_Geometry.h"
#include <memory.h>
#include <stdio.h>
#pragma region Dimension_Agnostic_Utility_Functions
// create a new object in heap
#define SLC_Polyliner32_CAlloc(__node_count) SLC_Array_Alloc((SLC_4i16_t){ \
    sizeof(SLC_r32_t), 4, __node_count, 1})
// create a new object in stack frame
#define SLC_Polyliner32_Calloca(__node_count) SLC_Array_Alloca((SLC_4i16_t){ \
    sizeof(SLC_r32_t), 4, __node_count, 1})

typedef struct {
    const SLC_r32_t *node0, *node1;
} SLC_PolylineSegmentr32_t, *SLC_PPolylineSegmentr32_t;
typedef const SLC_PolylineSegmentr32_t *SLC_PCPolylineSegmentr32_t;

// find a node with the minimum x coordinate
SLC_i16_t SLC_Polyliner32_MinX(SLC_PCArray_t polyline);

// find a node with the minimum y coordinate
SLC_i16_t SLC_Polyliner32_MinY(SLC_PCArray_t polyline);

// find a node with the minimum z coordinate
SLC_i16_t SLC_Polyliner32_MinZ(SLC_PCArray_t polyline);

// find a node with the maximum x coordinate
SLC_i16_t SLC_Polyliner32_MaxX(SLC_PCArray_t polyline);

// find a node with the maximum y coordinate
SLC_i16_t SLC_Polyliner32_MaxY(SLC_PCArray_t polyline);

// find a node with the maximum z coordinate
SLC_i16_t SLC_Polyliner32_MaxZ(SLC_PCArray_t polyline);

// extract coordinates of the two ends of a segment selected by index.
void SLC_Polyliner32_Segment(SLC_PCArray_t polyline, SLC_i16_t index,
    SLC_PPolylineSegmentr32_t segment);
#pragma endregion Dimension_Agnostic_Utility_Functions
#pragma region 2D_Utility_Functions
// create an array of pixels in the approximated vicinity
SLC_errno_t SLC_Segmentr32_ApproxPixels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuwv);

// create an array of pixels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr32_NearbyPixels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuwv);
#pragma endregion 2D_Utility_Functions
#pragma region 3D_Utility_Functions
// create an array of voxels in the approximated vicinity
SLC_errno_t SLC_Segmentr32_ApproxVoxels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuwv);

// check if a 3D voxel index uvw is on the line segment.
void SLC_Segmentr32_IsOn2D(SLC_PCPolylineSegmentr32_t segment,
    SLC_PCArray_t uvw, SLC_r32_t vicinityRadius, SLC_PArray_t isOn);

// create an array of voxels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr32_NearbyVoxels(SLC_PCPolylineSegmentr32_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuwv);
#pragma endregion 3D_Utility_Functions

#pragma region Dimension_Agnostic_Utility_Functions
// create a new object in heap
#define SLC_Polyliner64_CAlloc(__node_count) SLC_Array_Alloc((SLC_4i16_t){ \
    sizeof(SLC_r64_t), 4, __node_count, 1})
// create a new object in stack frame
#define SLC_Polyliner64_Calloca(__node_count) SLC_Array_Alloca((SLC_4i16_t){ \
    sizeof(SLC_r64_t), 4, __node_count, 1})

typedef struct {
    const SLC_r64_t *node0, *node1;
} SLC_PolylineSegmentr64_t, *SLC_PPolylineSegmentr64_t;
typedef const SLC_PolylineSegmentr64_t *SLC_PCPolylineSegmentr64_t;

// find a node with the minimum x coordinate
SLC_i16_t SLC_Polyliner64_MinX(SLC_PCArray_t polyline);

// find a node with the minimum y coordinate
SLC_i16_t SLC_Polyliner64_MinY(SLC_PCArray_t polyline);

// find a node with the minimum z coordinate
SLC_i16_t SLC_Polyliner64_MinZ(SLC_PCArray_t polyline);

// find a node with the maximum x coordinate
SLC_i16_t SLC_Polyliner64_MaxX(SLC_PCArray_t polyline);

// find a node with the maximum y coordinate
SLC_i16_t SLC_Polyliner64_MaxY(SLC_PCArray_t polyline);

// find a node with the maximum z coordinate
SLC_i16_t SLC_Polyliner64_MaxZ(SLC_PCArray_t polyline);

// extract coordinates of the two ends of a segment selected by index.
void SLC_Polyliner64_Segment(SLC_PCArray_t polyline, SLC_i16_t index,
    SLC_PPolylineSegmentr64_t segment);
#pragma endregion Dimension_Agnostic_Utility_Functions
#pragma region 2D_Utility_Functions
// create an array of pixels in the approximated vicinity
SLC_errno_t SLC_Segmentr64_ApproxPixels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuwv);

// create an array of pixels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr64_NearbyPixels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuwv);
#pragma endregion 2D_Utility_Functions
#pragma region 3D_Utility_Functions
// create an array of voxels in the approximated vicinity
SLC_errno_t SLC_Segmentr64_ApproxVoxels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuwv);

// check if a 3D voxel index uvw is on the line segment.
void SLC_Segmentr64_IsOn2D(SLC_PCPolylineSegmentr64_t segment,
    SLC_PCArray_t uvw, SLC_r64_t vicinityRadius, SLC_PArray_t isOn);

// create an array of voxels in the vicinity of the line segment
SLC_errno_t SLC_Segmentr64_NearbyVoxels(SLC_PCPolylineSegmentr64_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuwv);
#pragma endregion 3D_Utility_Functions

#endif
