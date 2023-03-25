#if !defined(_SLC_GEOMETRY_H)
#define _SLC_GEOMETRY_H
#include "SLC/SLC_MiniLA.h"
#include "SLC/SLC_Math.h"
#include <memory.h>

#pragma region r32_basic_geometrical_data_types
typedef SLC_r32_t* SLC_Pntr32_t;
typedef SLC_r32_t* SLC_Vecr32_t;
typedef SLC_r32_t* SLC_TMatr32_t;
typedef struct {
    SLC_r32_t r, cphi, sphi, ctheta, stheta;
} SLC_Polarr32_t, *SLC_PPolarr32_t;
typedef const SLC_Polarr32_t *SLC_PCPolarr32_t;
#pragma endregion r32_basic_geometrical_data_types

#pragma region r32_function_prototypes
// mprod = mleft * mright, and returned by SLC_TMatr32_Mul.
// work is used as work area. It must have more than 16 elements.
SLC_TMatr32_t SLC_TMatr32_Mul(
    SLC_TMatr32_t mleft, SLC_TMatr32_t mright, SLC_TMatr32_t mprod);

// minv = (m)^(-1)
// work is used as work area. It must have more than 40 elements.
SLC_TMatr32_t SLC_TMatr32_Inv(SLC_TMatr32_t m, SLC_TMatr32_t minv);

// transformed = m * original
// transform points in original to transformed.
SLC_r32_t* SLC_TMatr32_Transform(
    SLC_TMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed);
SLC_r32_t* SLC_TMatr32_MultiTransform(
    SLC_TMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed, SLC_size_t count);

// homogeneous coordinate 3D rotation matrix around Z axis; i.e. in x-y -plane
SLC_r32_t* SLC_TMatr32_rotateZ(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* resut);
#define SLC_TMatr32_rotateZrad(__rad, __result) \
    SLC_TMatr32_rotateZ(SLC_cosr32(__rad), SLC_sinr32(__rad), __result)
#define SLC_TMatr32_rotateZdeg(__deg, __result) \
    SLC_TMat<NT>_rotateZrad(SLC_r32deg2rad(__deg))

SLC_r32_t* SLC_TMatr32_rotateX(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result);
#define SLC_TMatr32_rotateXrad(__rad, __result) \
    SLC_TMatr32_rotateX(SLC_cosr32(__rad), SLC_sinr32(__rad), __result)
#define SLC_TMatr32_rotateXdeg(__deg, __result) \
    SLC_TMat<NT>_rotateXrad(SLC_r32deg2rad(__deg))

SLC_r32_t* SLC_TMatr32_rotateY(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result);
#define SLC_TMatr32_rotateYrad(__rad, __result) \
    SLC_TMatr32_rotateY(SLC_cosr32(__rad), SLC_sinr32(__rad), __result)
#define SLC_TMatr32_rotateYdeg(__deg, __result) \
    SLC_TMat<NT>_rotateYrad(SLC_r32deg2rad(__deg))

// polar-Cartesian coordinate translation
void SLC_PolarFromCartesianr32(SLC_PPolarr32_t polar, const SLC_Pntr32_t cartesian);
void SLC_PolarToCartesianr32(SLC_Pntr32_t cartesian, SLC_PCPolarr32_t polar);
#pragma endregion r32_function_prototypes

#pragma region r64_basic_geometrical_data_types
typedef SLC_r64_t* SLC_Pntr64_t;
typedef SLC_r64_t* SLC_Vecr64_t;
typedef SLC_r64_t* SLC_TMatr64_t;
typedef struct {
    SLC_r64_t r, cphi, sphi, ctheta, stheta;
} SLC_Polarr64_t, *SLC_PPolarr64_t;
typedef const SLC_Polarr64_t *SLC_PCPolarr64_t;
#pragma endregion r64_basic_geometrical_data_types

#pragma region r64_function_prototypes
// mprod = mleft * mright, and returned by SLC_TMatr64_Mul.
// work is used as work area. It must have more than 16 elements.
SLC_TMatr64_t SLC_TMatr64_Mul(
    SLC_TMatr64_t mleft, SLC_TMatr64_t mright, SLC_TMatr64_t mprod);

// minv = (m)^(-1)
// work is used as work area. It must have more than 40 elements.
SLC_TMatr64_t SLC_TMatr64_Inv(SLC_TMatr64_t m, SLC_TMatr64_t minv);

// transformed = m * original
// transform points in original to transformed.
SLC_r64_t* SLC_TMatr64_Transform(
    SLC_TMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed);
SLC_r64_t* SLC_TMatr64_MultiTransform(
    SLC_TMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed, SLC_size_t count);

// homogeneous coordinate 3D rotation matrix around Z axis; i.e. in x-y -plane
SLC_r64_t* SLC_TMatr64_rotateZ(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* resut);
#define SLC_TMatr64_rotateZrad(__rad, __result) \
    SLC_TMatr64_rotateZ(SLC_cosr64(__rad), SLC_sinr64(__rad), __result)
#define SLC_TMatr64_rotateZdeg(__deg, __result) \
    SLC_TMat<NT>_rotateZrad(SLC_r64deg2rad(__deg))

SLC_r64_t* SLC_TMatr64_rotateX(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result);
#define SLC_TMatr64_rotateXrad(__rad, __result) \
    SLC_TMatr64_rotateX(SLC_cosr64(__rad), SLC_sinr64(__rad), __result)
#define SLC_TMatr64_rotateXdeg(__deg, __result) \
    SLC_TMat<NT>_rotateXrad(SLC_r64deg2rad(__deg))

SLC_r64_t* SLC_TMatr64_rotateY(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result);
#define SLC_TMatr64_rotateYrad(__rad, __result) \
    SLC_TMatr64_rotateY(SLC_cosr64(__rad), SLC_sinr64(__rad), __result)
#define SLC_TMatr64_rotateYdeg(__deg, __result) \
    SLC_TMat<NT>_rotateYrad(SLC_r64deg2rad(__deg))

// polar-Cartesian coordinate translation
void SLC_PolarFromCartesianr64(SLC_PPolarr64_t polar, const SLC_Pntr64_t cartesian);
void SLC_PolarToCartesianr64(SLC_Pntr64_t cartesian, SLC_PCPolarr64_t polar);
#pragma endregion r64_function_prototypes
#endif
