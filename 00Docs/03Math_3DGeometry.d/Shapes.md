# Shapes
There are various shapes in the world. Some of them have their unit instance.
For example,
Table 1. Unit shapes
Name | Unit instance
-----|---------------
Sphere | R = 0.5, Center coordinate = (0, 0, 0)
Brick | Wx = Hy = Dz = 1, A corner is at (-0.5, -0.5, -0.5), The diagonal corner is at (0.5, 0.5, 0.5).
Cylinder | R = 0.5, Center of a face = (-0.5, 0, 0), Another center = (0.5, 0, 0)
Rectangle | T = 0.0, Wx = Hy = 1, A corner is at (-0.5, -0.5, 0), The diagonal corner is at (0.5, 0.5, 0).
Disk | R = 0.5, T = 0.0, Center is at (0, 0, 0), Normal vector = (0, 0, 1)
<br>

The shapes are enumerated in `SLC/SLC_Shapes.h`.  
An enum type is defined to represent the unit shapes.
```
// enumeration of unit shapes.
typedef enum {
    SLC_Shape_Sphere,
    SLC_Shape_Brick,
    SLC_Shape_Cylinder,
    SLC_Shape_Rectangle,
    SLC_Shape_Disk,
    SLC_Shape_Triangle,
    SLC_Shape_Tetrahedron,
} SLC_Shapes_t;
```
Each shape has its own feature points designated by enume types.
```
// Feature points of the unit shere
typedef enum {
    SLC_Sphere_FeaturePoint_Center, // (0, 0, 0)
    SLC_Sphere_FeaturePoint_Left, // (-0.5, 0, 0)
    SLC_Sphere_FeaturePoint_Right, // (0.5, 0, 0)
    SLC_Sphere_FeaturePoint_Bottom, // (0, -0.5, 0)
    SLC_Sphere_FeaturePoint_Top, // (0, 0.5, 0)
    SLC_Sphere_FeaturePoint_Rear, // (0, -0.5, 0)
    SLC_Sphere_FeaturePoint_Front, // (0, 0.5, 0)
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
    SLC_Tetrahedron_FeaturePoint_Left,
    SLC_Tetrahedron_FeaturePoint_Right,
    SLC_Tetrahedron_FeaturePoint_Rear,
    SLC_Tetrahedron_FeaturePoint_Top
} SLC_Tetrahedron_FeaturePoints_t;
```
The feature point coordinates are obtained a function defined in `SLC/SLC_Shapes.h`.  
```
// shape: enumeration of a shape
// featurePoint: (int) casted one of enum type of SLC_XXX_FeaturePoints_t.
// return the coordinate of the selected feature point.
SLC_CVec<NTID>_t SLC_Shapes_FeaturePoint(SLC_Shapes_t shape, int featurePoint);
```
