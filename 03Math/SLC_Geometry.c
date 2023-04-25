#include "SLC/SLC_Geometry.h"
#include "SLC/SLC_MiniLA.h"
#include "SLC/SLC_MiniBLAS.h"
static const SLC_r32_t IMat_r32[] = {
	1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f };
static const SLC_r64_t IMat_r64[] = {
	1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f };
#pragma region r32_function_impl
#pragma region matrix_multiplication
// 4x4 identity matrix
const SLC_CTMatr32_t SLC_TMatr32_IMat() { return (const SLC_TMatr32_t)IMat_r32; }

SLC_CTMatr32_t SLC_TMatr32_Mul(
    SLC_CTMatr32_t mleft, SLC_CTMatr32_t mright, SLC_TMatr32_t mprod
) {
    for (SLC_size_t row = 0; row < 4; row++)
    {
        const SLC_r32_t* _mright = mright;
        for (SLC_size_t column = 0; column < 4; column ++)
        {
            mprod[column + row * 4] =
                mleft[0] * _mright[0] + mleft[1] * _mright[4] +
                mleft[2] * _mright[8] + mleft[3] * _mright[12];
            _mright++;
        }
        mleft += 4;
    }
    return mprod;
}

#define MATSIZE4X4 { sizeof(SLC_r32_t), 4, 4, 1 }
#define MATSIZE5X8 { sizeof(SLC_r32_t), 8, 5, 1 }
SLC_CTMatr32_t SLC_TMatr32_Inv(SLC_CTMatr32_t m, SLC_TMatr32_t minv)
{
    SLC_4i16_t worksize = MATSIZE5X8;
    SLC_Array_t _m = { { MATSIZE4X4 }, { m } };
    SLC_Array_t _minv = { { MATSIZE4X4 }, { minv } };
    SLC_PArray_t _mwork = SLC_Array_Alloca(worksize);
    SLC_errno_t err = SLC_Matr32_Inv(&_minv, &_m, _mwork);
    return err ? NULL : minv;
}

const SLC_r32_t* SLC_TMatr32_Transform(
    SLC_CTMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed
) {
    transformed[0] = m[0] * original[0] + m[1] * original[1] + m[2] * original[2] + m[3] * original[3];
    transformed[1] = m[4] * original[0] + m[5] * original[1] + m[6] * original[2] + m[7] * original[3];
    transformed[2] = m[8] * original[0] + m[9] * original[1] + m[10] * original[2] + m[11] * original[3];
    transformed[3] = m[12] * original[0] + m[13] * original[1] + m[14] * original[2] + m[15] * original[3];
    return transformed;
}

const SLC_r32_t* SLC_TMatr32_MultiTransform(
    SLC_CTMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed, SLC_size_t count
) {
    const SLC_r32_t* _original = original;
    SLC_r32_t* _transformed = transformed;
    for (SLC_size_t i = 0; i < count; i++)
    {
        SLC_TMatr32_Transform(m, _original, _transformed);
        _original += 4;
        _transformed += 4;
    }
    return transformed;
}
#pragma endregion matrix_multiplication

#pragma region rotation_matrix
SLC_CTMatr32_t SLC_TMatr32_rotateZ(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result)
{
    memcpy(result, IMat_r32, sizeof(IMat_r32));
    result[0] = result[5] = c;
    result[1] = -(result[4] = s);
    return result;
}

SLC_CTMatr32_t SLC_TMatr32_rotateX(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result)
{
    memcpy(result, IMat_r32, sizeof(IMat_r32));
    result[5] = result[10] = c;
    result[6] = -(result[9] = s);
    return result;
}

SLC_CTMatr32_t SLC_TMatr32_rotateY(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result)
{
    memcpy(result, IMat_r32, sizeof(IMat_r32));
    result[0] = result[10] = c;
    result[8] = -(result[2] = s);
    return result;
}
#pragma endregion rotation_matrix

#pragma region polar_cartesian_conversion
void SLC_PolarFromCartesianr32(SLC_PPolarr32_t polar, SLC_CPntr32_t cartesian)
{
    SLC_r32_t _w = SLC_r32_units[1]/cartesian[3];
    SLC_3r32_t xyz = { _w * cartesian[0], _w * cartesian[1], _w * cartesian[2] };
    SLC_r32_t Rh = SLC_r32sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1]);
    polar->r = SLC_r32sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2]);
    polar->cphi = xyz[0]/Rh;
    polar->sphi = xyz[1]/Rh;
    polar->ctheta = Rh/polar->r;
    polar->stheta = xyz[2]/polar->r;
}

void SLC_PolarToCartesianr32(SLC_Pntr32_t cartesian, SLC_PCPolarr32_t polar)
{
    cartesian[0] = polar->r * polar->ctheta * polar->cphi;
    cartesian[1] = polar->r * polar->ctheta * polar->sphi;
    cartesian[2] = polar->r * polar->stheta;
    cartesian[3] = SLC_r32_units[1];
}
#pragma region polar_cartesian_conversion
SLC_CVecr32_t SLC_Vecr32_CrossProduct(SLC_CVecr32_t x0, SLC_CVecr32_t x1, SLC_Vecr32_t result)
{
    result[0] = x0[1] * x1[2] - x1[1] * x0[2];
    result[1] = x0[2] * x1[0] - x1[2] * x0[0];
    result[2] = x0[0] * x1[1] - x1[0] * x0[1];
    result[3] = x0[3] * x1[3];
    return result;
}
#pragma region printing
void SLC_TMatr32_Print(FILE* out, SLC_CTMatr32_t mat)
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            const char* delimiter = (column == 0) ? "" : ", ";
            SLC_r32_print(out, delimiter, mat[column + row*4]);
        }
        fprintf(out, "\n");
    }
}

void SLC_Pntr32_Print(FILE* out, SLC_CPntr32_t pnt)
{
    SLC_r32_print(out, "", pnt[0]);
    SLC_r32_print(out, ", ", pnt[1]);
    SLC_r32_print(out, ", ", pnt[2]);
    SLC_r32_print(out, ", ", pnt[3]);
    SLC_r32_print(out, ",(", pnt[0]/pnt[3]);
    SLC_r32_print(out, ", ", pnt[1]/pnt[3]);
    SLC_r32_print(out, ", ", pnt[2]/pnt[3]);
    fprintf(out, ")\n");
}

void SLC_Vecr32_Print(FILE* out, SLC_CVecr32_t vec)
{
    SLC_r32_print(out, "", vec[0]);
    SLC_r32_print(out, ", ", vec[1]);
    SLC_r32_print(out, ", ", vec[2]);
    SLC_r32_print(out, ", ", vec[3]);
    SLC_r32_print(out, ",(", vec[0]/vec[3]);
    SLC_r32_print(out, ", ", vec[1]/vec[3]);
    SLC_r32_print(out, ", ", vec[2]/vec[3]);
    fprintf(out, ")\n");
}

SLC_r32_t SLC_Vecr32_InnerProduct(SLC_CVecr32_t v0, SLC_CVecr32_t v1)
{
    SLC_r32_t normalizer = SLC_r32_units[1] / (v0[3] * v1[3]);
    return normalizer * (v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2]);
}

SLC_errno_t SLC_Vecr32_Normalize(SLC_Vecr32_t vnormalized, SLC_CVecr32_t vsrc)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r32_t L2norm = SLC_r32sqrt(SLC_Vecr32_InnerProduct(vsrc, vsrc));
        if (L2norm < SLC_r32_stdtol)
        {
            err = SLC_ESINGULAR;
            break;
        }
        SLC_r32_t normalizer = SLC_r32_units[1] / (L2norm * vsrc[3]);
        vnormalized[0] = vsrc[0] * normalizer;
        vnormalized[1] = vsrc[1] * normalizer;
        vnormalized[2] = vsrc[2] * normalizer;
        vnormalized[3] = SLC_r32_units[1];
    } while (0);
    return err;
}

void SLC_Vecr32_Vector(SLC_Vecr32_t v, SLC_CPntr32_t pbegin, SLC_CPntr32_t pend)
{
    const SLC_r32_t _1 = SLC_r32_units[1];
    const SLC_r32_t pbegin_normalizer = _1 / pbegin[3];
    const SLC_r32_t pend_normalizer = _1 / pend[3];
    v[0] = pend_normalizer * pend[0] - pbegin_normalizer * pbegin[0];
    v[1] = pend_normalizer * pend[1] - pbegin_normalizer * pbegin[1];
    v[2] = pend_normalizer * pend[2] - pbegin_normalizer * pbegin[2];
    v[3] = _1;
}

#pragma endregion printing
#pragma region high-level_geometry_functions
/*!
\brief Create a line object from two 3D points in homobeneous coordinate
\param line [out] line object
\param p0 [in] a point
\param p1 [in] another point
\return SLC_ESINGULAR if p0 and p1 are too close.
*/
SLC_errno_t SLC_Liner32_Property
(SLC_PLinePlaner32_t line, const SLC_Pntr32_t p0, const SLC_Pntr32_t p1)
{
    SLC_COPY4(line->p0, p0);
    SLC_Vecr32_t p1p0;
    SLC_Vecr32_Vector(p1p0, p0, p1);
    return SLC_Vecr32_Normalize(line->v0, p1p0);
}

/*!
\brief Create a plane object from three 3D points in homobeneous coordinate
\param plane [out] plane object
\param p0 [in] a point
\param p1 [in] another point
\param p2 [in] 2nd another point
\return SLC_ESINGULAR if |(p1-p0)x(p2-p0)| is too small
*/
SLC_errno_t SLC_Planer32_Property
(SLC_PLinePlaner32_t plane, const SLC_Pntr32_t p0, const SLC_Pntr32_t p1, const SLC_Pntr32_t p2)
{
    SLC_Vecr32_t p0p1, p0p2, p0p1_x_p0p2;
    SLC_Vecr32_Vector(p0p1, p0, p1);
    SLC_Vecr32_Vector(p0p2, p0, p2);
    SLC_Vecr32_CrossProduct(p0p1, p0p2, p0p1_x_p0p2);
    SLC_COPY4(plane->p0, p0);
    return SLC_Vecr32_Normalize(plane->v0, p0p1_x_p0p2);
}

SLC_bool_t SLC_Liner32_IsIn(SLC_PCLinePlaner32_t line, SLC_CPntr32_t pnt, SLC_r32_t tol)
{
    SLC_r32_t _1 = SLC_r32_units[1];
    SLC_r32_t pnt_scaling = _1 / pnt[3];
    SLC_r32_t p0_scaling = _1 / line->p0[3];
    SLC_4r32_t pnt_p0 = 
    {
        pnt[0] * pnt_scaling - line->p0[0] * p0_scaling,
        pnt[1] * pnt_scaling - line->p0[1] * p0_scaling,
        pnt[2] * pnt_scaling - line->p0[2] * p0_scaling,
        _1
    };
    SLC_r32_t pnt_p0_length = SLC_r32sqrt(SLC_Vecr32_InnerProduct(pnt_p0, pnt_p0));
    if (pnt_p0_length < tol)
    {
        return true;
    }
    SLC_r32_t normalizer = _1 / pnt_p0_length;
    pnt_p0[0] *= normalizer;
    pnt_p0[1] *= normalizer;
    pnt_p0[2] *= normalizer;
    SLC_r32_t discrimination_param = SLC_Vecr32_InnerProduct(pnt_p0, line->v0);
    return (SLC_r32_abs(discrimination_param - _1) < tol) ||
        (SLC_r32_abs(discrimination_param + _1) < tol);
}

void SLC_LinePlaner32_Print(FILE* out, SLC_PCLinePlaner32_t lineplane)
{
    fprintf(out, "Line-Plane:\n\tp0: ");
    SLC_Vecr32_Print(out, lineplane->p0);
    fprintf(out, ",\n\tv0: ");
    SLC_Vecr32_Print(out, lineplane->p0);
    fprintf(out, "\n");
}

SLC_bool_t SLC_Planer32_IsIn(SLC_PCLinePlaner32_t plane, SLC_CPntr32_t pnt, SLC_r32_t tol)
{
    SLC_r32_t _1 = SLC_r32_units[1];
    SLC_r32_t pnt_scaling = _1 / pnt[3];
    SLC_r32_t p0_scaling = _1 / plane->p0[3];
    SLC_4r32_t pnt_p0 = 
    {
        pnt[0] * pnt_scaling - plane->p0[0] * p0_scaling,
        pnt[1] * pnt_scaling - plane->p0[1] * p0_scaling,
        pnt[2] * pnt_scaling - plane->p0[2] * p0_scaling,
        _1
    };
    SLC_r32_t pnt_p0_length = SLC_r32sqrt(SLC_Vecr32_InnerProduct(pnt_p0, pnt_p0));
    if (pnt_p0_length < tol)
    {
        return true;
    }
    SLC_r32_t normalizer = _1 / pnt_p0_length;
    pnt_p0[0] *= normalizer;
    pnt_p0[1] *= normalizer;
    pnt_p0[2] *= normalizer;
    SLC_r32_t discrimination_param = SLC_Vecr32_InnerProduct(pnt_p0, plane->v0);
    return SLC_r32_abs(discrimination_param) < tol;
}

SLC_errno_t SLC_LinePlaner32_Crosssection(
    SLC_PCLinePlaner32_t line, SLC_PCLinePlaner32_t plane, SLC_Pntr32_t cross)
{
    const SLC_r32_t _1 = SLC_r32_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r32_t a;
        SLC_4r32_t p1_p0;
        SLC_r32_t DN = SLC_Vecr32_InnerProduct(line->v0, plane->v0);
        if (SLC_r32_abs(DN) < SLC_r32_stdtol)
        { // line and plane are nearly parallel.
            err = SLC_ESINGULAR;
            break;
        }
        p1_p0[0] = plane->p0[0] * line->p0[3] - line->p0[0] * plane->p0[3];
        p1_p0[1] = plane->p0[1] * line->p0[3] - line->p0[1] * plane->p0[3];
        p1_p0[2] = plane->p0[2] * line->p0[3] - line->p0[2] * plane->p0[3];
        p1_p0[3] = plane->p0[3] * line->p0[3];
        a = SLC_Vecr32_InnerProduct(p1_p0, plane->v0) / DN;
        { // calc crosssection coordinate
            SLC_r32_t normalizerP0 = _1 / line->p0[3];
            SLC_r32_t normalizerD = _1 / line->v0[3];
            cross[0] = normalizerP0 * line->p0[0] + a * normalizerD * line->v0[0];
            cross[1] = normalizerP0 * line->p0[1] + a * normalizerD * line->v0[1];
            cross[2] = normalizerP0 * line->p0[2] + a * normalizerD * line->v0[2];
            cross[3] = _1;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_Planer32_2Crosssection(SLC_PCLinePlaner32_t planes, SLC_PLinePlaner32_t cross)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_LinePlaner32_t _3planes[3];
    do {
        memcpy(_3planes, planes, 2 * sizeof(SLC_LinePlaner32_t));
        SLC_Vecr32_CrossProduct(planes[0].v0, planes[1].v0, _3planes[2].v0);
        SLC_COPY4(_3planes[2].p0, planes[0].p0);
        err = SLC_Planer32_3Crosssection(_3planes, cross->p0);
        SLC_COPY4(cross->v0, _3planes[2].v0)
    } while (0);
    return err;
}

SLC_errno_t SLC_Planer32_3Crosssection(SLC_PCLinePlaner32_t planes, SLC_Pntr32_t cross)
{
    const SLC_r32_t _1 = SLC_r32_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_4i16_t left_size = { sizeof(SLC_r32_t), 3, 3, 1 }, right_size = { sizeof(SLC_r32_t), 1, 3, 1 };
    SLC_4i16_t work_size = SLC_SolveWorkSize(left_size, right_size);
    SLC_PArray_t left = SLC_Array_Alloca(left_size), right = SLC_Array_Alloca(right_size),
        work = SLC_Array_Alloca(work_size);
    SLC_Array_t px = { { sizeof(SLC_r32_t), 1, 3, 1 }, { cross } };
    do {
        left->data._r32[0] = planes[0].v0[0];
        left->data._r32[1] = planes[0].v0[1];
        left->data._r32[2] = planes[0].v0[2];
        left->data._r32[3] = planes[1].v0[0];
        left->data._r32[4] = planes[1].v0[1];
        left->data._r32[5] = planes[1].v0[2];
        left->data._r32[6] = planes[2].v0[0];
        left->data._r32[7] = planes[2].v0[1];
        left->data._r32[8] = planes[2].v0[2];
        right->data._r32[0] = SLC_Vecr32_InnerProduct(planes[0].p0, planes[0].v0);
        right->data._r32[1] = SLC_Vecr32_InnerProduct(planes[1].p0, planes[1].v0);
        right->data._r32[2] = SLC_Vecr32_InnerProduct(planes[2].p0, planes[2].v0);
        SLC_Matr32_Solve(&px, left, right, work);
    } while (0);
    return err;
}
#pragma endregion high-level_geometry_functions
#undef MATSIZE4X4
#undef MATSIZE5X8
#pragma endregion r32_function_impl
#pragma region r64_function_impl
#pragma region matrix_multiplication
// 4x4 identity matrix
const SLC_CTMatr64_t SLC_TMatr64_IMat() { return (const SLC_TMatr64_t)IMat_r64; }

SLC_CTMatr64_t SLC_TMatr64_Mul(
    SLC_CTMatr64_t mleft, SLC_CTMatr64_t mright, SLC_TMatr64_t mprod
) {
    for (SLC_size_t row = 0; row < 4; row++)
    {
        const SLC_r64_t* _mright = mright;
        for (SLC_size_t column = 0; column < 4; column ++)
        {
            mprod[column + row * 4] =
                mleft[0] * _mright[0] + mleft[1] * _mright[4] +
                mleft[2] * _mright[8] + mleft[3] * _mright[12];
            _mright++;
        }
        mleft += 4;
    }
    return mprod;
}

#define MATSIZE4X4 { sizeof(SLC_r64_t), 4, 4, 1 }
#define MATSIZE5X8 { sizeof(SLC_r64_t), 8, 5, 1 }
SLC_CTMatr64_t SLC_TMatr64_Inv(SLC_CTMatr64_t m, SLC_TMatr64_t minv)
{
    SLC_4i16_t worksize = MATSIZE5X8;
    SLC_Array_t _m = { { MATSIZE4X4 }, { m } };
    SLC_Array_t _minv = { { MATSIZE4X4 }, { minv } };
    SLC_PArray_t _mwork = SLC_Array_Alloca(worksize);
    SLC_errno_t err = SLC_Matr64_Inv(&_minv, &_m, _mwork);
    return err ? NULL : minv;
}

const SLC_r64_t* SLC_TMatr64_Transform(
    SLC_CTMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed
) {
    transformed[0] = m[0] * original[0] + m[1] * original[1] + m[2] * original[2] + m[3] * original[3];
    transformed[1] = m[4] * original[0] + m[5] * original[1] + m[6] * original[2] + m[7] * original[3];
    transformed[2] = m[8] * original[0] + m[9] * original[1] + m[10] * original[2] + m[11] * original[3];
    transformed[3] = m[12] * original[0] + m[13] * original[1] + m[14] * original[2] + m[15] * original[3];
    return transformed;
}

const SLC_r64_t* SLC_TMatr64_MultiTransform(
    SLC_CTMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed, SLC_size_t count
) {
    const SLC_r64_t* _original = original;
    SLC_r64_t* _transformed = transformed;
    for (SLC_size_t i = 0; i < count; i++)
    {
        SLC_TMatr64_Transform(m, _original, _transformed);
        _original += 4;
        _transformed += 4;
    }
    return transformed;
}
#pragma endregion matrix_multiplication

#pragma region rotation_matrix
SLC_CTMatr64_t SLC_TMatr64_rotateZ(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result)
{
    memcpy(result, IMat_r64, sizeof(IMat_r64));
    result[0] = result[5] = c;
    result[1] = -(result[4] = s);
    return result;
}

SLC_CTMatr64_t SLC_TMatr64_rotateX(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result)
{
    memcpy(result, IMat_r64, sizeof(IMat_r64));
    result[5] = result[10] = c;
    result[6] = -(result[9] = s);
    return result;
}

SLC_CTMatr64_t SLC_TMatr64_rotateY(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result)
{
    memcpy(result, IMat_r64, sizeof(IMat_r64));
    result[0] = result[10] = c;
    result[8] = -(result[2] = s);
    return result;
}
#pragma endregion rotation_matrix

#pragma region polar_cartesian_conversion
void SLC_PolarFromCartesianr64(SLC_PPolarr64_t polar, SLC_CPntr64_t cartesian)
{
    SLC_r64_t _w = SLC_r64_units[1]/cartesian[3];
    SLC_3r64_t xyz = { _w * cartesian[0], _w * cartesian[1], _w * cartesian[2] };
    SLC_r64_t Rh = SLC_r64sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1]);
    polar->r = SLC_r64sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2]);
    polar->cphi = xyz[0]/Rh;
    polar->sphi = xyz[1]/Rh;
    polar->ctheta = Rh/polar->r;
    polar->stheta = xyz[2]/polar->r;
}

void SLC_PolarToCartesianr64(SLC_Pntr64_t cartesian, SLC_PCPolarr64_t polar)
{
    cartesian[0] = polar->r * polar->ctheta * polar->cphi;
    cartesian[1] = polar->r * polar->ctheta * polar->sphi;
    cartesian[2] = polar->r * polar->stheta;
    cartesian[3] = SLC_r64_units[1];
}
#pragma region polar_cartesian_conversion
SLC_CVecr64_t SLC_Vecr64_CrossProduct(SLC_CVecr64_t x0, SLC_CVecr64_t x1, SLC_Vecr64_t result)
{
    result[0] = x0[1] * x1[2] - x1[1] * x0[2];
    result[1] = x0[2] * x1[0] - x1[2] * x0[0];
    result[2] = x0[0] * x1[1] - x1[0] * x0[1];
    result[3] = x0[3] * x1[3];
    return result;
}
#pragma region printing
void SLC_TMatr64_Print(FILE* out, SLC_CTMatr64_t mat)
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            const char* delimiter = (column == 0) ? "" : ", ";
            SLC_r64_print(out, delimiter, mat[column + row*4]);
        }
        fprintf(out, "\n");
    }
}

void SLC_Pntr64_Print(FILE* out, SLC_CPntr64_t pnt)
{
    SLC_r64_print(out, "", pnt[0]);
    SLC_r64_print(out, ", ", pnt[1]);
    SLC_r64_print(out, ", ", pnt[2]);
    SLC_r64_print(out, ", ", pnt[3]);
    SLC_r64_print(out, ",(", pnt[0]/pnt[3]);
    SLC_r64_print(out, ", ", pnt[1]/pnt[3]);
    SLC_r64_print(out, ", ", pnt[2]/pnt[3]);
    fprintf(out, ")\n");
}

void SLC_Vecr64_Print(FILE* out, SLC_CVecr64_t vec)
{
    SLC_r64_print(out, "", vec[0]);
    SLC_r64_print(out, ", ", vec[1]);
    SLC_r64_print(out, ", ", vec[2]);
    SLC_r64_print(out, ", ", vec[3]);
    SLC_r64_print(out, ",(", vec[0]/vec[3]);
    SLC_r64_print(out, ", ", vec[1]/vec[3]);
    SLC_r64_print(out, ", ", vec[2]/vec[3]);
    fprintf(out, ")\n");
}

SLC_r64_t SLC_Vecr64_InnerProduct(SLC_CVecr64_t v0, SLC_CVecr64_t v1)
{
    SLC_r64_t normalizer = SLC_r64_units[1] / (v0[3] * v1[3]);
    return normalizer * (v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2]);
}

SLC_errno_t SLC_Vecr64_Normalize(SLC_Vecr64_t vnormalized, SLC_CVecr64_t vsrc)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r64_t L2norm = SLC_r64sqrt(SLC_Vecr64_InnerProduct(vsrc, vsrc));
        if (L2norm < SLC_r64_stdtol)
        {
            err = SLC_ESINGULAR;
            break;
        }
        SLC_r64_t normalizer = SLC_r64_units[1] / (L2norm * vsrc[3]);
        vnormalized[0] = vsrc[0] * normalizer;
        vnormalized[1] = vsrc[1] * normalizer;
        vnormalized[2] = vsrc[2] * normalizer;
        vnormalized[3] = SLC_r64_units[1];
    } while (0);
    return err;
}

void SLC_Vecr64_Vector(SLC_Vecr64_t v, SLC_CPntr64_t pbegin, SLC_CPntr64_t pend)
{
    const SLC_r64_t _1 = SLC_r64_units[1];
    const SLC_r64_t pbegin_normalizer = _1 / pbegin[3];
    const SLC_r64_t pend_normalizer = _1 / pend[3];
    v[0] = pend_normalizer * pend[0] - pbegin_normalizer * pbegin[0];
    v[1] = pend_normalizer * pend[1] - pbegin_normalizer * pbegin[1];
    v[2] = pend_normalizer * pend[2] - pbegin_normalizer * pbegin[2];
    v[3] = _1;
}

#pragma endregion printing
#pragma region high-level_geometry_functions
/*!
\brief Create a line object from two 3D points in homobeneous coordinate
\param line [out] line object
\param p0 [in] a point
\param p1 [in] another point
\return SLC_ESINGULAR if p0 and p1 are too close.
*/
SLC_errno_t SLC_Liner64_Property
(SLC_PLinePlaner64_t line, const SLC_Pntr64_t p0, const SLC_Pntr64_t p1)
{
    SLC_COPY4(line->p0, p0);
    SLC_Vecr64_t p1p0;
    SLC_Vecr64_Vector(p1p0, p0, p1);
    return SLC_Vecr64_Normalize(line->v0, p1p0);
}

/*!
\brief Create a plane object from three 3D points in homobeneous coordinate
\param plane [out] plane object
\param p0 [in] a point
\param p1 [in] another point
\param p2 [in] 2nd another point
\return SLC_ESINGULAR if |(p1-p0)x(p2-p0)| is too small
*/
SLC_errno_t SLC_Planer64_Property
(SLC_PLinePlaner64_t plane, const SLC_Pntr64_t p0, const SLC_Pntr64_t p1, const SLC_Pntr64_t p2)
{
    SLC_Vecr64_t p0p1, p0p2, p0p1_x_p0p2;
    SLC_Vecr64_Vector(p0p1, p0, p1);
    SLC_Vecr64_Vector(p0p2, p0, p2);
    SLC_Vecr64_CrossProduct(p0p1, p0p2, p0p1_x_p0p2);
    SLC_COPY4(plane->p0, p0);
    return SLC_Vecr64_Normalize(plane->v0, p0p1_x_p0p2);
}

SLC_bool_t SLC_Liner64_IsIn(SLC_PCLinePlaner64_t line, SLC_CPntr64_t pnt, SLC_r64_t tol)
{
    SLC_r64_t _1 = SLC_r64_units[1];
    SLC_r64_t pnt_scaling = _1 / pnt[3];
    SLC_r64_t p0_scaling = _1 / line->p0[3];
    SLC_4r64_t pnt_p0 = 
    {
        pnt[0] * pnt_scaling - line->p0[0] * p0_scaling,
        pnt[1] * pnt_scaling - line->p0[1] * p0_scaling,
        pnt[2] * pnt_scaling - line->p0[2] * p0_scaling,
        _1
    };
    SLC_r64_t pnt_p0_length = SLC_r64sqrt(SLC_Vecr64_InnerProduct(pnt_p0, pnt_p0));
    if (pnt_p0_length < tol)
    {
        return true;
    }
    SLC_r64_t normalizer = _1 / pnt_p0_length;
    pnt_p0[0] *= normalizer;
    pnt_p0[1] *= normalizer;
    pnt_p0[2] *= normalizer;
    SLC_r64_t discrimination_param = SLC_Vecr64_InnerProduct(pnt_p0, line->v0);
    return (SLC_r64_abs(discrimination_param - _1) < tol) ||
        (SLC_r64_abs(discrimination_param + _1) < tol);
}

void SLC_LinePlaner64_Print(FILE* out, SLC_PCLinePlaner64_t lineplane)
{
    fprintf(out, "Line-Plane:\n\tp0: ");
    SLC_Vecr64_Print(out, lineplane->p0);
    fprintf(out, ",\n\tv0: ");
    SLC_Vecr64_Print(out, lineplane->p0);
    fprintf(out, "\n");
}

SLC_bool_t SLC_Planer64_IsIn(SLC_PCLinePlaner64_t plane, SLC_CPntr64_t pnt, SLC_r64_t tol)
{
    SLC_r64_t _1 = SLC_r64_units[1];
    SLC_r64_t pnt_scaling = _1 / pnt[3];
    SLC_r64_t p0_scaling = _1 / plane->p0[3];
    SLC_4r64_t pnt_p0 = 
    {
        pnt[0] * pnt_scaling - plane->p0[0] * p0_scaling,
        pnt[1] * pnt_scaling - plane->p0[1] * p0_scaling,
        pnt[2] * pnt_scaling - plane->p0[2] * p0_scaling,
        _1
    };
    SLC_r64_t pnt_p0_length = SLC_r64sqrt(SLC_Vecr64_InnerProduct(pnt_p0, pnt_p0));
    if (pnt_p0_length < tol)
    {
        return true;
    }
    SLC_r64_t normalizer = _1 / pnt_p0_length;
    pnt_p0[0] *= normalizer;
    pnt_p0[1] *= normalizer;
    pnt_p0[2] *= normalizer;
    SLC_r64_t discrimination_param = SLC_Vecr64_InnerProduct(pnt_p0, plane->v0);
    return SLC_r64_abs(discrimination_param) < tol;
}

SLC_errno_t SLC_LinePlaner64_Crosssection(
    SLC_PCLinePlaner64_t line, SLC_PCLinePlaner64_t plane, SLC_Pntr64_t cross)
{
    const SLC_r64_t _1 = SLC_r64_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r64_t a;
        SLC_4r64_t p1_p0;
        SLC_r64_t DN = SLC_Vecr64_InnerProduct(line->v0, plane->v0);
        if (SLC_r64_abs(DN) < SLC_r64_stdtol)
        { // line and plane are nearly parallel.
            err = SLC_ESINGULAR;
            break;
        }
        p1_p0[0] = plane->p0[0] * line->p0[3] - line->p0[0] * plane->p0[3];
        p1_p0[1] = plane->p0[1] * line->p0[3] - line->p0[1] * plane->p0[3];
        p1_p0[2] = plane->p0[2] * line->p0[3] - line->p0[2] * plane->p0[3];
        p1_p0[3] = plane->p0[3] * line->p0[3];
        a = SLC_Vecr64_InnerProduct(p1_p0, plane->v0) / DN;
        { // calc crosssection coordinate
            SLC_r64_t normalizerP0 = _1 / line->p0[3];
            SLC_r64_t normalizerD = _1 / line->v0[3];
            cross[0] = normalizerP0 * line->p0[0] + a * normalizerD * line->v0[0];
            cross[1] = normalizerP0 * line->p0[1] + a * normalizerD * line->v0[1];
            cross[2] = normalizerP0 * line->p0[2] + a * normalizerD * line->v0[2];
            cross[3] = _1;
        }
    } while (0);
    return err;
}

SLC_errno_t SLC_Planer64_2Crosssection(SLC_PCLinePlaner64_t planes, SLC_PLinePlaner64_t cross)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_LinePlaner64_t _3planes[3];
    do {
        memcpy(_3planes, planes, 2 * sizeof(SLC_LinePlaner64_t));
        SLC_Vecr64_CrossProduct(planes[0].v0, planes[1].v0, _3planes[2].v0);
        SLC_COPY4(_3planes[2].p0, planes[0].p0);
        err = SLC_Planer64_3Crosssection(_3planes, cross->p0);
        SLC_COPY4(cross->v0, _3planes[2].v0)
    } while (0);
    return err;
}

SLC_errno_t SLC_Planer64_3Crosssection(SLC_PCLinePlaner64_t planes, SLC_Pntr64_t cross)
{
    const SLC_r64_t _1 = SLC_r64_units[1];
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_4i16_t left_size = { sizeof(SLC_r64_t), 3, 3, 1 }, right_size = { sizeof(SLC_r64_t), 1, 3, 1 };
    SLC_4i16_t work_size = SLC_SolveWorkSize(left_size, right_size);
    SLC_PArray_t left = SLC_Array_Alloca(left_size), right = SLC_Array_Alloca(right_size),
        work = SLC_Array_Alloca(work_size);
    SLC_Array_t px = { { sizeof(SLC_r64_t), 1, 3, 1 }, { cross } };
    do {
        left->data._r64[0] = planes[0].v0[0];
        left->data._r64[1] = planes[0].v0[1];
        left->data._r64[2] = planes[0].v0[2];
        left->data._r64[3] = planes[1].v0[0];
        left->data._r64[4] = planes[1].v0[1];
        left->data._r64[5] = planes[1].v0[2];
        left->data._r64[6] = planes[2].v0[0];
        left->data._r64[7] = planes[2].v0[1];
        left->data._r64[8] = planes[2].v0[2];
        right->data._r64[0] = SLC_Vecr64_InnerProduct(planes[0].p0, planes[0].v0);
        right->data._r64[1] = SLC_Vecr64_InnerProduct(planes[1].p0, planes[1].v0);
        right->data._r64[2] = SLC_Vecr64_InnerProduct(planes[2].p0, planes[2].v0);
        SLC_Matr64_Solve(&px, left, right, work);
    } while (0);
    return err;
}
#pragma endregion high-level_geometry_functions
#undef MATSIZE4X4
#undef MATSIZE5X8
#pragma endregion r64_function_impl
