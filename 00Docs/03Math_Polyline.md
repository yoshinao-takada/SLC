# Polyline
It defines a data structure of 3D polylines in homogeneous coordinate
and utility functions for 2D manipulation and 3D manipulation of the polylines.
In the case of 2D manipulation, z component is a constant in a whole polyline;
i.e. the polyline is parallel with z-plane.

Table 1. size component of `SLC_Array_t` for a polyline
Component | Description
----------|--------------
cont.i16[0] | sizeof(SLC_r32_t) or sizeof(SLC_r64_t)
cont.i16[1] | always 4 (dimension of 3D homogeneous coordinate)
cont.i16[2] | node count of a polyline
cont.i16[3] | always 1
<br/>

Note: In the following description, `<NTID>` is `r32` for `SLC_r32_t` elements or `r64` for `SLC_r64_t`
elements.

## Dimension Agnostic Utility Functions
```
// create a new object in heap
#define SLC_Polyline<NTID>_CAlloc(__node_count) ...
// create a new object in stack frame
#define SLC_Polyline<NTID>_Calloca(__node_count) ...

typedef struct {
    const SLC_<NTID>_t *node0, *node1;
} SLC_PolylineSegment<NTID>_t, *SLC_PPolylineSegment<NTID>_t;
typedef const SLC_PolylineSegment<NTID>_t *SLC_PCPolylineSegment<NTID>_t;

// find a node with the minimum x coordinate
SLC_i16_t SLC_Polyline<NTID>_MinX(SLC_PCArray_t polyline);

// find a node with the minimum y coordinate
SLC_i16_t SLC_Polyline<NTID>_MinY(SLC_PCArray_t polyline);

// find a node with the minimum z coordinate
SLC_i16_t SLC_Polyline<NTID>_MinZ(SLC_PCArray_t polyline);

// find a node with the maximum x coordinate
SLC_i16_t SLC_Polyline<NTID>_MaxX(SLC_PCArray_t polyline);

// find a node with the maximum y coordinate
SLC_i16_t SLC_Polyline<NTID>_MaxY(SLC_PCArray_t polyline);

// find a node with the maximum z coordinate
SLC_i16_t SLC_Polyline<NTID>_MaxZ(SLC_PCArray_t polyline);

// extract coordinates of the two ends of a segment selected by index.
void SLC_Polyline<NTID>_Segment(SLC_PCArray_t polyline, SLC_i16_t index,
    SLC_PPolylineSegment<NTID>_t segment);
```

## 2D Utility Functions
```
// create an array of pixels in the approximated vicinity
SLC_errno_t SLC_Segment<NTID>_ApproxPixels(SLC_PCPolylineSegment<NTID>_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuwv);

// create an array of pixels in the vicinity of the line segment
SLC_errno_t SLC_Segment<NTID>_NearbyPixels(SLC_PCPolylineSegment<NTID>_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuwv);
```
## 3D Utility Functions
```
// create an array of voxels in the approximated vicinity
SLC_errno_t SLC_Segment<NTID>_ApproxVoxels(SLC_PCPolylineSegment<NTID>_t segment,
    SLC_i16_t approxRadius, SLC_PArray_t* ppuwv);

// check if a 3D voxel index uvw is on the line segment.
void SLC_Segment<NTID>_IsOn2D(SLC_PCPolylineSegment<NTID>_t segment,
    SLC_PCArray_t uvw, SLC_<NTID>_t vicinityRadius, SLC_PArray_t isOn);

// create an array of voxels in the vicinity of the line segment
SLC_errno_t SLC_Segment<NTID>_NearbyVoxels(SLC_PCPolylineSegment<NTID>_t segment,
    SLC_i16_t vicinityRadius, SLC_PArray_t* ppuwv);
```
