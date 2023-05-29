#include "SLC/SLC_Shapes.h"

static const SLC_r32_t fpr32_Sphere[] = 
{
    0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
    0.0f, -0.5f, 0.0f, 1.0f,
    0.0f, 0.5f, 0.0f, 1.0f,
    0.0f, 0.0f, -0.5f, 1.0f,
    0.0f, 0.0f, 0.5f, 1.0f,
};

static const SLC_r32_t fpr32_Brick[] = 
{
    -0.5f, -0.5f, -0.5f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f,
};

static const SLC_r32_t fpr32_Cylinder[] = 
{
    -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
};

static const SLC_r32_t fpr32_Rectangle[] = 
{
    -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
};

static const SLC_r32_t fpr32_Disk[] = 
{
    -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
    0.0f, -0.5f, 0.0f, 1.0f,
    0.0f, 0.5f, 0.0f, 1.0f,
};

static const SLC_r32_t fpr32_Triangle[] = 
{
    -0.5f, -0.2887f, 0.0f, 1.0f,
    0.5f, -0.2887f, 0.0f, 1.0f,
    0.0f, 0.5774f, 0.0f, 1.0f,
};

static const SLC_r32_t fpr32_Tetrahedron[] = 
{
    -0.5f, -0.2887f, -0.2041f, 1.0f,
    0.5f, -0.2887f, -0.2041f, 1.0f,
    0.0f, -0.5774f, -0.2041f, 1.0f,
    0.0f, 0.0f, 0.6124f, 1.0f
};

static const SLC_r32_t* fpr32[] =
{
    fpr32_Sphere, fpr32_Brick, fpr32_Cylinder, fpr32_Rectangle, fpr32_Disk,
    fpr32_Triangle, fpr32_Tetrahedron,
};

static const SLC_r64_t fpr64_Sphere[] = 
{
    0.0, 0.0, 0.0, 1.0,
    -0.5, 0.0, 0.0, 1.0,
    0.5, 0.0, 0.0, 1.0,
    0.0, -0.5, 0.0, 1.0,
    0.0, 0.5, 0.0, 1.0,
    0.0, 0.0, -0.5, 1.0,
    0.0, 0.0, 0.5, 1.0,
};

static const SLC_r64_t fpr64_Brick[] = 
{
    -0.5, -0.5, -0.5, 1.0,
    0.5, -0.5, -0.5, 1.0,
    -0.5, 0.5, -0.5, 1.0,
    0.5, 0.5, -0.5, 1.0,
    -0.5, -0.5, 0.5, 1.0,
    0.5, -0.5, 0.5, 1.0,
    -0.5, 0.5, 0.5, 1.0,
    0.5, 0.5, 0.5, 1.0,
};

static const SLC_r64_t fpr64_Cylinder[] = 
{
    -0.5, 0.0, 0.0, 1.0,
    0.5, 0.0, 0.0, 1.0,
};

static const SLC_r64_t fpr64_Rectangle[] = 
{
    -0.5, -0.5, 0.0, 1.0,
    0.5, -0.5, 0.0, 1.0,
    -0.5, 0.5, 0.0, 1.0,
    0.5, 0.5, 0.0, 1.0,
};

static const SLC_r64_t fpr64_Disk[] = 
{
    -0.5, 0.0, 0.0, 1.0,
    0.5, 0.0, 0.0, 1.0,
    0.0, -0.5, 0.0, 1.0,
    0.0, 0.5, 0.0, 1.0,
};

static const SLC_r64_t fpr64_Triangle[] = 
{
    -0.5, -0.2887, 0.0, 1.0,
    0.5, -0.2887, 0.0, 1.0,
    0.0, 0.5774, 0.0, 1.0,
};

static const SLC_r64_t fpr64_Tetrahedron[] = 
{
    -0.5, -0.2887, -0.2041, 1.0,
    0.5, -0.2887, -0.2041, 1.0,
    0.0, -0.5774, -0.2041, 1.0,
    0.0, 0.0, 0.6124, 1.0
};

static const SLC_r64_t* fpr64[] =
{
    fpr64_Sphere, fpr64_Brick, fpr64_Cylinder, fpr64_Rectangle, fpr64_Disk,
    fpr64_Triangle, fpr64_Tetrahedron
};

SLC_CPntr32_t SLC_Shapes_FeaturePointr32(SLC_Shapes_t shape, int featurePoint)
{
    return fpr32[(int)shape] + 4 * featurePoint;
}

SLC_CPntr64_t SLC_Shapes_FeaturePointr64(SLC_Shapes_t shape, int featurePoint)
{
    return fpr64[(int)shape] + 4 * featurePoint;
}