#if !defined(_SLC_Camera_H)
#define _SLC_Camera_H
#include "SLC/SLC_Geometry.h"
#define IMat_r32 { \
	1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, \
	0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f }
#define IMat_r64 { \
	1.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 0.0, \
	0.0, 0.0, 1.0, 0.0,  0.0, 0.0, 0.0, 1.0 }
#pragma region Camera-matrix-with-basetype-r32
// create a camera position matrix
typedef struct {
    SLC_4r32_t cameraIsAt;
    SLC_4r32_t lookAt;
    SLC_2r32_t viewAxisRotationCosSin;
} SLC_CameraPositionr32_t, *SLC_PCameraPositionr32_t;
typedef const SLC_CameraPositionr32_t *SLC_PCCameraPositionr32_t;

// create a camera opsition matrix.
// It transforms 
// object vertex coordinates in world coordinate system
// to those in camera coordinate system.
// It is the inverse of camera position coordinate and attitude in the world coordinate system.
SLC_CTMatr32_t SLC_Camerar32_Position(SLC_PCCameraPositionr32_t pos, SLC_TMatr32_t work);

// create a direction rotatioin matrix from (0,0,-1) to cameraIsAt => cameraLookAt vector
SLC_CTMatr32_t SLC_Camerar32_Direction(
    SLC_CPntr32_t cameraIsAt, SLC_CPntr32_t cameraLookAt, SLC_Vecr32_t work);

typedef struct {
    SLC_2r32_t width_height;
    SLC_2r32_t far_near; // far: negative larger number, near: usually negative smaller number
} SLC_Projectionr32_t, *SLC_PProjectionr32_t;
typedef const SLC_Projectionr32_t *SLC_PCProjectionr32_t;

// create a camera projection matrix of orthnormal mode
SLC_CTMatr32_t SLC_Camerar32_Orth(
    SLC_PCProjectionr32_t projconf,
    SLC_TMatr32_t work);

// create a camera projection matrix of perspective mode
SLC_CTMatr32_t SLC_Camerar32_Perspective(
    SLC_PCProjectionr32_t projconf,
    SLC_TMatr32_t work);
#pragma endregion Camera-matrix-with-basetype-r32
#pragma region Camera-matrix-with-basetype-r64
// create a camera position matrix
typedef struct {
    SLC_4r64_t cameraIsAt;
    SLC_4r64_t lookAt;
    SLC_2r64_t viewAxisRotationCosSin;
} SLC_CameraPositionr64_t, *SLC_PCameraPositionr64_t;
typedef const SLC_CameraPositionr64_t *SLC_PCCameraPositionr64_t;

// create a camera opsition matrix.
// It transforms 
// object vertex coordinates in world coordinate system
// to those in camera coordinate system.
// It is the inverse of camera position coordinate and attitude in the world coordinate system.
SLC_CTMatr64_t SLC_Camerar64_Position(SLC_PCCameraPositionr64_t pos, SLC_TMatr64_t work);

// create a direction rotatioin matrix from (0,0,-1) to cameraIsAt => cameraLookAt vector
SLC_CTMatr64_t SLC_Camerar64_Direction(
    SLC_CPntr64_t cameraIsAt, SLC_CPntr64_t cameraLookAt, SLC_Vecr64_t work);

typedef struct {
    SLC_2r64_t width_height;
    SLC_2r64_t far_near; // far: negative larger number, near: usually negative smaller number
} SLC_Projectionr64_t, *SLC_PProjectionr64_t;
typedef const SLC_Projectionr64_t *SLC_PCProjectionr64_t;

// create a camera projection matrix of orthnormal mode
SLC_CTMatr64_t SLC_Camerar64_Orth(
    SLC_PCProjectionr64_t projconf,
    SLC_TMatr64_t work);

// create a camera projection matrix of perspective mode
SLC_CTMatr64_t SLC_Camerar64_Perspective(
    SLC_PCProjectionr64_t projconf,
    SLC_TMatr64_t work);
#pragma endregion Camera-matrix-with-basetype-r64
#endif
