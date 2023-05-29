#if !defined(SLC_SHAPES_H)
#define SLC_SHAPES_H
#include <SLC/SLC_Geometry.h>

// enumeration of unit shapes.
typedef enum {
    SLC_Shape_Sphere,
    SLC_Shape_Brick,
    SLC_Shape_Cylinder,
    SLC_Shape_Rectangle,
    SLC_Shape_Disk,
    SLC_Shape_EquilateralTriangle,
    SLC_Shape_Tetrahedron,
} SLC_Shapes_t;

// Feature points of the unit shere
typedef enum {
    SLC_Sphere_FeaturePoint_Center, // (0, 0, 0)
    SLC_Sphere_FeaturePoint_Left, // (-0.5, 0, 0)
    SLC_Sphere_FeaturePoint_Right, // (0.5, 0, 0)
    SLC_Sphere_FeaturePoint_Bottom, // (0, -0.5, 0)
    SLC_Sphere_FeaturePoint_Top, // (0, 0.5, 0)
    SLC_Sphere_FeaturePoint_Rear, // (0, 0, -0.5)
    SLC_Sphere_FeaturePoint_Front, // (0, 0, 0.5)
} SLC_Sphere_FeaturePoints_t;

// Feature points of the unit brick
typedef enum {
    SLC_Brick_FeaturePoint_LBR, // left-bottom-rear (-0.5, -0.5, -0.5)
    SLC_Brick_FeaturePoint_RBR, // right-bottom-rear (0.5, -0.5, -0.5)
    SLC_Brick_FeaturePoint_LTR, // left-top-rear (-0.5, 0.5, -0.5)
    SLC_Brick_FeaturePoint_RTR, // right-top-rear (0.5, 0.5, -0.5)
    SLC_Brick_FeaturePoint_LBF, // left-bottom-rear (-0.5, -0.5, 0.5)
    SLC_Brick_FeaturePoint_RBF, // right-bottom-rear (0.5, -0.5, 0.5)
    SLC_Brick_FeaturePoint_LTF, // left-top-rear (-0.5, 0.5, 0.5)
    SLC_Brick_FeaturePoint_RTF, // right-top-rear (0.5, 0.5, 0.5)
} SLC_Brick_FeaturePoints_t;

// Feature points of the unit cylinder
typedef enum {
    SLC_Cylinder_FeaturePoint_Left, // left circular face center (-0.5, 0, 0)
    SLC_Cylinder_FeaturePoint_Right, // right circular face center (0.5, 0, 0)
} SLC_Cylinder_FeaturePoints_t;

// Feature points of the unit rectangle
typedef enum {
    SLC_Rectangle_FeaturePoint_LB, // left-bottom (-0.5, -0.5, 0)
    SLC_Rectangle_FeaturePoint_RB, // right-bottom (0.5, -0.5, 0)
    SLC_Rectangle_FeaturePoint_LT, // left-top (-0.5, 0.5, 0)
    SLC_Rectangle_FeaturePoint_RT, // right-top (0.5, 0.5, 0)
} SLC_Rectangle_FeaturePoints_t;

// Feature points of the unit disk
typedef enum {
    SLC_Disk_FeaturePoint_Left, // (-0.5, 0, 0)
    SLC_Disk_FeaturePoint_Right, // (0.5, 0, 0)
    SLC_Disk_FeaturePoint_Bottom, // (0, -0.5, 0)
    SLC_Disk_FeaturePoint_Top, // (0, 0.5, 0)
} SLC_Disk_FeaturePoints_t;

// Feature points of the unit equilateral triangle
typedef enum {
    SLC_EquilateralTriangle_FeaturePoint_Left, // (-0.5, -1/(2*sqrt(3)), 0)
    SLC_EquilateralTriangle_FeaturePoint_Right, // (0.5, -1/(2*sqrt(3)), 0)
    SLC_EquilateralTriangle_FeaturePoint_Top, // (0, 1/sqrt(3), 0)
} SLC_EquilateralTriangle_FeaturePoints_t;

typedef enum {
    SLC_Tetrahedron_FeaturePoint_Left, // (-0.5, -1/(2*sqrt(3)), -1/(2*sqrt(6)))
    SLC_Tetrahedron_FeaturePoint_Right, // (+0.5, -1/(2*sqrt(3)), -1/(2*sqrt(6)))
    SLC_Tetrahedron_FeaturePoint_Rear, // (0, -1/sqrt(3), -1/(2*sqrt(6)))
    SLC_Tetrahedron_FeaturePoint_Top, // (0, 0, sqrt(3)/(2*sqrt(2)))
} SLC_Tetrahedron_FeaturePoints_t;

// Get a 3D homogeneous coordinate with w = 1.0
SLC_CPntr32_t SLC_Shapes_FeaturePointr32(SLC_Shapes_t shape, int featurePoint);

// Get a 3D homogeneous coordinate with w = 1.0
SLC_CPntr64_t SLC_Shapes_FeaturePointr64(SLC_Shapes_t shape, int featurePoint);
#endif