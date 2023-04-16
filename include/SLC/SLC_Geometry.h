#if !defined(_SLC_GEOMETRY_H)
#define _SLC_GEOMETRY_H
#include "SLC/SLC_MiniLA.h"
#include "SLC/SLC_Math.h"
#include <memory.h>
#include <stdio.h>

#pragma region r32_basic_geometrical_data_types
typedef SLC_r32_t* SLC_Pntr32_t;
typedef SLC_r32_t* SLC_Vecr32_t;
typedef SLC_r32_t* SLC_TMatr32_t;
typedef const SLC_r32_t* SLC_CPntr32_t;
typedef const SLC_r32_t* SLC_CVecr32_t;
typedef const SLC_r32_t* SLC_CTMatr32_t;

typedef struct {
    SLC_r32_t r, cphi, sphi, ctheta, stheta;
} SLC_Polarr32_t, *SLC_PPolarr32_t;
typedef const SLC_Polarr32_t *SLC_PCPolarr32_t;
#pragma endregion r32_basic_geometrical_data_types

#pragma region r32_function_prototypes
// 4x4 identity matrix
SLC_CTMatr32_t const SLC_TMatr32_IMat();

// mprod = mleft * mright, and returned by SLC_TMatr32_Mul.
// work is used as work area. It must have more than 16 elements.
SLC_CTMatr32_t SLC_TMatr32_Mul(
    SLC_CTMatr32_t mleft, SLC_CTMatr32_t mright, SLC_TMatr32_t mprod);

// minv = (m)^(-1)
// work is used as work area. It must have more than 40 elements.
SLC_CTMatr32_t SLC_TMatr32_Inv(SLC_CTMatr32_t m, SLC_TMatr32_t minv);

// transformed = m * original
// transform points in original to transformed.
const SLC_r32_t* SLC_TMatr32_Transform(
    SLC_CTMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed);
const SLC_r32_t* SLC_TMatr32_MultiTransform(
    SLC_CTMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed, SLC_size_t count);

// homogeneous coordinate 3D rotation matrix around Z axis; i.e. in x-y -plane
SLC_CTMatr32_t SLC_TMatr32_rotateZ(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* resut);
#define SLC_TMatr32_rotateZrad(__rad, __result) \
    SLC_TMatr32_rotateZ(SLC_r32cos(__rad), SLC_r32sin(__rad), __result)
#define SLC_TMatr32_rotateZdeg(__deg, __result) \
    SLC_TMatr32_rotateZrad(SLC_r32deg2rad(__deg), __result)

SLC_CTMatr32_t SLC_TMatr32_rotateX(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result);
#define SLC_TMatr32_rotateXrad(__rad, __result) \
    SLC_TMatr32_rotateX(SLC_r32cos(__rad), SLC_r32sin(__rad), __result)
#define SLC_TMatr32_rotateXdeg(__deg, __result) \
    SLC_TMatr32_rotateXrad(SLC_r32deg2rad(__deg), __result)

SLC_CTMatr32_t SLC_TMatr32_rotateY(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result);
#define SLC_TMatr32_rotateYrad(__rad, __result) \
    SLC_TMatr32_rotateY(SLC_r32cos(__rad), SLC_r32sin(__rad), __result)
#define SLC_TMatr32_rotateYdeg(__deg, __result) \
    SLC_TMatr32_rotateYrad(SLC_r32deg2rad(__deg), __result)

// polar-Cartesian coordinate translation
void SLC_PolarFromCartesianr32(SLC_PPolarr32_t polar, SLC_CPntr32_t cartesian);
void SLC_PolarToCartesianr32(SLC_Pntr32_t cartesian, SLC_PCPolarr32_t polar);

SLC_CVecr32_t SLC_Vecr32_CrossProduct(SLC_CVecr32_t x0, SLC_CVecr32_t x1, SLC_Vecr32_t result);
// print
void SLC_TMatr32_Print(FILE* out, SLC_CTMatr32_t mat);
void SLC_Pntr32_Print(FILE* out, SLC_CPntr32_t pnt);
void SLC_Vecr32_Print(FILE* out, SLC_CVecr32_t vec);

#pragma region high-level_geometry_functions
SLC_r32_t SLC_Vecr32_InnerProduct(SLC_CVecr32_t v0, SLC_CVecr32_t v1);

// A line and a plane can be represented by a point and a unit vector.
typedef struct {
    SLC_4r32_t p0; // reference point
    SLC_4r32_t v0; // direction of line or normal of plane
} SLC_LinePlaner32_t, *SLC_PLinePlaner32_t;
typedef const SLC_LinePlaner32_t *SLC_PCLinePlaner32_t;

/*!
\brief Print Line-plane object
\param out [in] output stream
\param lineplane [in] object to print
*/
void SLC_LinePlaner32_Print(FILE* out, SLC_PCLinePlaner32_t lineplane);

/*!
\brief Return true if pnt is in line.
\param line [in] reference line
\param pnt [in] target point to discriminate.
\param tol [in] criteria to discriminate an absolute value of an inner product 
                of two unit vectors is nearly equal to 1 or not.
\return true: pnt is in line, false: pnt is NOT in line.
*/
SLC_bool_t SLC_Liner32_IsIn(SLC_PCLinePlaner32_t line, SLC_CPntr32_t pnt, SLC_r32_t tol);

// Return true if pnt is in plane. tol is a criteria in discriminating two unit vector product is
// nearly equal to 0 or not.
/*!
\brief Return false if pnt is not in plane.
\param plane [in] reference plane
\param pnt [in] target point to discriminate
\param tol [in] criteria to discriminate an inner product of two unit vectors is nearly equal to 0 or not.
\return true: pnt is in line, false: pnt is NOT in line.
*/
SLC_bool_t SLC_Planer32_IsIn(SLC_PCLinePlaner32_t plane, SLC_CPntr32_t pnt, SLC_r32_t tol);

/*!
\brief Get a crosssection of a line and a plane.
\param line [in] reference point and direction vector of the line
\param plane [in] reference point and normal vector of the plane
\param cross [out] crosssection of the line and the plane
\return SLC_ESINGULAR(line and plane are parallel) or EXIT_SUCCESS
*/
SLC_errno_t SLC_LinePlaner32_Crosssection(
    SLC_PCLinePlaner32_t line, SLC_PCLinePlaner32_t plane, SLC_Pntr32_t cross);

/*!
\brief Crosssection of three planes
\param planes [in]
\param cross [out]
\return SLC_ESINGULAR (two of three planes are near parallel) or EXIT_SUCCESS.
*/
SLC_errno_t SLC_Planer32_2Crosssection(SLC_PCLinePlaner32_t planes, SLC_PLinePlaner32_t cross);


/*!
\brief Crosssection of three planes
\param planes [in]
\param cross [out]
\return SLC_ESINGULAR (two of three planes are near parallel) or EXIT_SUCCESS.
*/
SLC_errno_t SLC_Planer32_3Crosssection(SLC_PCLinePlaner32_t planes, SLC_Pntr32_t cross);
#pragma endregion high-level_geometry_functions
#pragma endregion r32_function_prototypes

#pragma region r64_basic_geometrical_data_types
typedef SLC_r64_t* SLC_Pntr64_t;
typedef SLC_r64_t* SLC_Vecr64_t;
typedef SLC_r64_t* SLC_TMatr64_t;
typedef const SLC_r64_t* SLC_CPntr64_t;
typedef const SLC_r64_t* SLC_CVecr64_t;
typedef const SLC_r64_t* SLC_CTMatr64_t;

typedef struct {
    SLC_r64_t r, cphi, sphi, ctheta, stheta;
} SLC_Polarr64_t, *SLC_PPolarr64_t;
typedef const SLC_Polarr64_t *SLC_PCPolarr64_t;
#pragma endregion r64_basic_geometrical_data_types

#pragma region r64_function_prototypes
// 4x4 identity matrix
SLC_CTMatr64_t const SLC_TMatr64_IMat();

// mprod = mleft * mright, and returned by SLC_TMatr64_Mul.
// work is used as work area. It must have more than 16 elements.
SLC_CTMatr64_t SLC_TMatr64_Mul(
    SLC_CTMatr64_t mleft, SLC_CTMatr64_t mright, SLC_TMatr64_t mprod);

// minv = (m)^(-1)
// work is used as work area. It must have more than 40 elements.
SLC_CTMatr64_t SLC_TMatr64_Inv(SLC_CTMatr64_t m, SLC_TMatr64_t minv);

// transformed = m * original
// transform points in original to transformed.
const SLC_r64_t* SLC_TMatr64_Transform(
    SLC_CTMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed);
const SLC_r64_t* SLC_TMatr64_MultiTransform(
    SLC_CTMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed, SLC_size_t count);

// homogeneous coordinate 3D rotation matrix around Z axis; i.e. in x-y -plane
SLC_CTMatr64_t SLC_TMatr64_rotateZ(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* resut);
#define SLC_TMatr64_rotateZrad(__rad, __result) \
    SLC_TMatr64_rotateZ(SLC_r64cos(__rad), SLC_r64sin(__rad), __result)
#define SLC_TMatr64_rotateZdeg(__deg, __result) \
    SLC_TMatr64_rotateZrad(SLC_r64deg2rad(__deg), __result)

SLC_CTMatr64_t SLC_TMatr64_rotateX(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result);
#define SLC_TMatr64_rotateXrad(__rad, __result) \
    SLC_TMatr64_rotateX(SLC_r64cos(__rad), SLC_r64sin(__rad), __result)
#define SLC_TMatr64_rotateXdeg(__deg, __result) \
    SLC_TMatr64_rotateXrad(SLC_r64deg2rad(__deg), __result)

SLC_CTMatr64_t SLC_TMatr64_rotateY(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result);
#define SLC_TMatr64_rotateYrad(__rad, __result) \
    SLC_TMatr64_rotateY(SLC_r64cos(__rad), SLC_r64sin(__rad), __result)
#define SLC_TMatr64_rotateYdeg(__deg, __result) \
    SLC_TMatr64_rotateYrad(SLC_r64deg2rad(__deg), __result)

// polar-Cartesian coordinate translation
void SLC_PolarFromCartesianr64(SLC_PPolarr64_t polar, SLC_CPntr64_t cartesian);
void SLC_PolarToCartesianr64(SLC_Pntr64_t cartesian, SLC_PCPolarr64_t polar);

SLC_CVecr64_t SLC_Vecr64_CrossProduct(SLC_CVecr64_t x0, SLC_CVecr64_t x1, SLC_Vecr64_t result);
// print
void SLC_TMatr64_Print(FILE* out, SLC_CTMatr64_t mat);
void SLC_Pntr64_Print(FILE* out, SLC_CPntr64_t pnt);
void SLC_Vecr64_Print(FILE* out, SLC_CVecr64_t vec);

#pragma region high-level_geometry_functions
SLC_r64_t SLC_Vecr64_InnerProduct(SLC_CVecr64_t v0, SLC_CVecr64_t v1);

// A line and a plane can be represented by a point and a unit vector.
typedef struct {
    SLC_4r64_t p0; // reference point
    SLC_4r64_t v0; // direction of line or normal of plane
} SLC_LinePlaner64_t, *SLC_PLinePlaner64_t;
typedef const SLC_LinePlaner64_t *SLC_PCLinePlaner64_t;

/*!
\brief Print Line-plane object
\param out [in] output stream
\param lineplane [in] object to print
*/
void SLC_LinePlaner64_Print(FILE* out, SLC_PCLinePlaner64_t lineplane);

/*!
\brief Return true if pnt is in line.
\param line [in] reference line
\param pnt [in] target point to discriminate.
\param tol [in] criteria to discriminate an absolute value of an inner product 
                of two unit vectors is nearly equal to 1 or not.
\return true: pnt is in line, false: pnt is NOT in line.
*/
SLC_bool_t SLC_Liner64_IsIn(SLC_PCLinePlaner64_t line, SLC_CPntr64_t pnt, SLC_r64_t tol);

// Return true if pnt is in plane. tol is a criteria in discriminating two unit vector product is
// nearly equal to 0 or not.
/*!
\brief Return false if pnt is not in plane.
\param plane [in] reference plane
\param pnt [in] target point to discriminate
\param tol [in] criteria to discriminate an inner product of two unit vectors is nearly equal to 0 or not.
\return true: pnt is in line, false: pnt is NOT in line.
*/
SLC_bool_t SLC_Planer64_IsIn(SLC_PCLinePlaner64_t plane, SLC_CPntr64_t pnt, SLC_r64_t tol);

/*!
\brief Get a crosssection of a line and a plane.
\param line [in] reference point and direction vector of the line
\param plane [in] reference point and normal vector of the plane
\param cross [out] crosssection of the line and the plane
\return SLC_ESINGULAR(line and plane are parallel) or EXIT_SUCCESS
*/
SLC_errno_t SLC_LinePlaner64_Crosssection(
    SLC_PCLinePlaner64_t line, SLC_PCLinePlaner64_t plane, SLC_Pntr64_t cross);

/*!
\brief Crosssection of three planes
\param planes [in]
\param cross [out]
\return SLC_ESINGULAR (two of three planes are near parallel) or EXIT_SUCCESS.
*/
SLC_errno_t SLC_Planer64_2Crosssection(SLC_PCLinePlaner64_t planes, SLC_PLinePlaner64_t cross);


/*!
\brief Crosssection of three planes
\param planes [in]
\param cross [out]
\return SLC_ESINGULAR (two of three planes are near parallel) or EXIT_SUCCESS.
*/
SLC_errno_t SLC_Planer64_3Crosssection(SLC_PCLinePlaner64_t planes, SLC_Pntr64_t cross);
#pragma endregion high-level_geometry_functions
#pragma endregion r64_function_prototypes
#endif
