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
const SLC_TMatr32_t SLC_TMatr32_IMat() { return (const SLC_TMatr32_t)IMat_r32; }

SLC_TMatr32_t SLC_TMatr32_Mul(
    SLC_TMatr32_t mleft, SLC_TMatr32_t mright, SLC_TMatr32_t mprod
) {
    for (SLC_size_t row = 0; row < 4; row++)
    {
        for (SLC_size_t column = 0; column < 4; column ++)
        {
            mprod[column + row * 4] =
                mleft[0] * mright[0] + mleft[1] * mright[4] +
                mleft[2] * mright[8] + mleft[3] * mright[12];
            mright++;
        }
        mleft += 4;
    }
    return mprod;
}

#define MATSIZE4X4 { sizeof(SLC_r32_t), 4, 4, 1 }
#define MATSIZE5X8 { sizeof(SLC_r32_t), 8, 5, 1 }
SLC_TMatr32_t SLC_TMatr32_Inv(SLC_TMatr32_t m, SLC_TMatr32_t minv)
{
    SLC_4i16_t worksize = MATSIZE5X8;
    SLC_Array_t _m = { { MATSIZE4X4 }, { m } };
    SLC_Array_t _minv = { { MATSIZE4X4 }, { minv } };
    SLC_PArray_t _mwork = SLC_Array_Alloca(worksize);
    SLC_errno_t err = SLC_Matr32_Inv(&_minv, &_m, _mwork);
    return err ? NULL : minv;
}

SLC_r32_t* SLC_TMatr32_Transform(
    SLC_TMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed
) {
    transformed[0] = m[0] * original[0] + m[1] * original[1] + m[2] * original[2] + m[3] * original[3];
    transformed[1] = m[4] * original[0] + m[5] * original[1] + m[6] * original[2] + m[7] * original[3];
    transformed[2] = m[8] * original[0] + m[9] * original[1] + m[10] * original[2] + m[11] * original[3];
    transformed[3] = m[12] * original[0] + m[13] * original[1] + m[14] * original[2] + m[15] * original[3];
    return transformed;
}

SLC_r32_t* SLC_TMatr32_MultiTransform(
    SLC_TMatr32_t m, const SLC_r32_t* original, SLC_r32_t* transformed, SLC_size_t count
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
SLC_r32_t* SLC_TMatr32_rotateZ(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result)
{
    memcpy(result, IMat_r32, sizeof(IMat_r32));
    result[0] = result[5] = c;
    result[1] = -(result[4] = s);
    return result;
}

SLC_r32_t* SLC_TMatr32_rotateX(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result)
{
    memcpy(result, IMat_r32, sizeof(IMat_r32));
    result[5] = result[10] = c;
    result[9] = -(result[6] = s);
    return result;
}

SLC_r32_t* SLC_TMatr32_rotateY(SLC_r32_t c, SLC_r32_t s, SLC_r32_t* result)
{
    memcpy(result, IMat_r32, sizeof(IMat_r32));
    result[0] = result[10] = c;
    result[8] = -(result[2] = s);
    return result;
}
#pragma endregion rotation_matrix

#pragma region polar_cartesian_conversion
void SLC_PolarFromCartesianr32(SLC_PPolarr32_t polar, const SLC_Pntr32_t cartesian)
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
#undef MATSIZE4X4
#undef MATSIZE5X8
#pragma endregion r32_function_impl
#pragma region r64_function_impl
#pragma region matrix_multiplication
// 4x4 identity matrix
const SLC_TMatr64_t SLC_TMatr64_IMat() { return (const SLC_TMatr64_t)IMat_r64; }

SLC_TMatr64_t SLC_TMatr64_Mul(
    SLC_TMatr64_t mleft, SLC_TMatr64_t mright, SLC_TMatr64_t mprod
) {
    for (SLC_size_t row = 0; row < 4; row++)
    {
        for (SLC_size_t column = 0; column < 4; column ++)
        {
            mprod[column + row * 4] =
                mleft[0] * mright[0] + mleft[1] * mright[4] +
                mleft[2] * mright[8] + mleft[3] * mright[12];
            mright++;
        }
        mleft += 4;
    }
    return mprod;
}

#define MATSIZE4X4 { sizeof(SLC_r64_t), 4, 4, 1 }
#define MATSIZE5X8 { sizeof(SLC_r64_t), 8, 5, 1 }
SLC_TMatr64_t SLC_TMatr64_Inv(SLC_TMatr64_t m, SLC_TMatr64_t minv)
{
    SLC_4i16_t worksize = MATSIZE5X8;
    SLC_Array_t _m = { { MATSIZE4X4 }, { m } };
    SLC_Array_t _minv = { { MATSIZE4X4 }, { minv } };
    SLC_PArray_t _mwork = SLC_Array_Alloca(worksize);
    SLC_errno_t err = SLC_Matr64_Inv(&_minv, &_m, _mwork);
    return err ? NULL : minv;
}

SLC_r64_t* SLC_TMatr64_Transform(
    SLC_TMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed
) {
    transformed[0] = m[0] * original[0] + m[1] * original[1] + m[2] * original[2] + m[3] * original[3];
    transformed[1] = m[4] * original[0] + m[5] * original[1] + m[6] * original[2] + m[7] * original[3];
    transformed[2] = m[8] * original[0] + m[9] * original[1] + m[10] * original[2] + m[11] * original[3];
    transformed[3] = m[12] * original[0] + m[13] * original[1] + m[14] * original[2] + m[15] * original[3];
    return transformed;
}

SLC_r64_t* SLC_TMatr64_MultiTransform(
    SLC_TMatr64_t m, const SLC_r64_t* original, SLC_r64_t* transformed, SLC_size_t count
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
SLC_r64_t* SLC_TMatr64_rotateZ(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result)
{
    memcpy(result, IMat_r64, sizeof(IMat_r64));
    result[0] = result[5] = c;
    result[1] = -(result[4] = s);
    return result;
}

SLC_r64_t* SLC_TMatr64_rotateX(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result)
{
    memcpy(result, IMat_r64, sizeof(IMat_r64));
    result[5] = result[10] = c;
    result[9] = -(result[6] = s);
    return result;
}

SLC_r64_t* SLC_TMatr64_rotateY(SLC_r64_t c, SLC_r64_t s, SLC_r64_t* result)
{
    memcpy(result, IMat_r64, sizeof(IMat_r64));
    result[0] = result[10] = c;
    result[8] = -(result[2] = s);
    return result;
}
#pragma endregion rotation_matrix

#pragma region polar_cartesian_conversion
void SLC_PolarFromCartesianr64(SLC_PPolarr64_t polar, const SLC_Pntr64_t cartesian)
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
#undef MATSIZE4X4
#undef MATSIZE5X8
#pragma endregion r64_function_impl
