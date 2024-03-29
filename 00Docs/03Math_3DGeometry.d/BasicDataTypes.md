# 3D Math Basic Data Types
## Overview
The data types listed below are defined in `SLC_GeometryBase.c/.h`.
* Point and vector are treated as 4 dimensional vector of `SLC_r32_t` or `SLC_r64_t` and are represented by
homogeneous coordinates. 
* Rotation and Linear Transform is always a 4x4 matrix of `SLC_r32_t` or `SLC_r64_t`.
* Polar coordinate is treated as five element struct, `r`, `cphi`, `sphi`, `ctheta`, `stheta`.
* An angle is represented by its cosine and sine (`c` and `s`).

Note:  
* Only right-handed is allowed in Cartesian coordinate system.
* Angle in z-plane increases counter-clockwise seen from a z-axis positive point.
In other planes, angles increases in the same manner.
* Polar coordinate _&phi;_ is angle in z-plane starting from x-axis. _&theta;_ is and elevation
angle originated from z-plane. _&theta;_ is positive in positive _z_ hemisphere and negative in
negative _z_ hemisphere. This configuration is suitable to radio and optical measurement systems.

## Point and Vector
Point and vector are declared as shown below.
```
typedef SLC_r32_t* SLC_Pntr32_t, SLC_Vecr32_t;
typedef SLC_r64_t* SLC_Pntr64_t, SLC_Vecr64_t;
```
The code snippets are examples using points and vectors.
```
SLC_4r32_t point0, point1, vector;

// function prototype Foo
// vector is filled with (end - begin) and returned by Foo.
SLC_Vecr32_t Foo(SLC_Pntr32_t begin, SLC_Pntr32_t end, SLC_Vecr32_t vector);

SLC_Pntr32_t result = Foo(point0, point1, vector);
```
## Rotation and Linear Transform
Only multiplication is applicable to transform matrices. Therefore only three mathematical operations
are defined for transform matrices.
```
typedef SLC_r32_t* SLC_TMatr32_t;
typedef SLC_r64_t* SLC_TMatr64_t;

// mprod = mleft * mright, and returned by SLC_TMatr32_Mul.
// work is used as work area. It must have more than 16 elements.
SLC_TMatr32_t SLC_TMatr32_Mul(
    SLC_TMatr32_t mleft, SLC_TMatr32_t mright, SLC_TMatr32_t mprod, SLC_r32_t* work);
SLC_TMatr64_t SLC_TMatr64_Mul(
    SLC_TMatr64_t mleft, SLC_TMatr64_t mright, SLC_TMatr64_t mprod, SLC_r64_t* work);

// minv = (m)^(-1)
// work is used as work area. It must have more than 40 elements.
SLC_TMatr32_t SLC_TMatr32_Inv(
    SLC_TMatr32_t m, SLC_TMatr32_t minv, SLC_r32_t* work);
SLC_TMatr64_t SLC_TMatr64_Inv(
    SLC_TMatr64_t m, SLC_TMatr64_t minv, SLC_r64_t* work);

// transformed = m * original
// transform points in original to transformed.
SLC_r32_t* SLC_TMatr32_Transform(SLC_TMatr32_t m, const SLC_r32_t* points, SLC_r32_t* transformed);
SLC_r64_t* SLC_TMatr64_Transform(SLC_TMatr64_t m, const SLC_r64_t* points, SLC_r64_t* transformed);
```
### __Rotation Transform__
CCW rotation seen from positive Z axis is defined as
$$\begin{equation}\begin{bmatrix}x_1 \\ y_1\end{bmatrix}=\begin{bmatrix}
    \cos(A_{\text{z}}) & -\sin(A_{\text{z}}) \\
    \sin(A_{\text{z}}) & \cos(A_{\text{z}}) \\
\end{bmatrix}\begin{bmatrix}x_0 \\ y_0\end{bmatrix}
\end{equation}$$
, where $A_{\text{z}}$ is a rotatioin angle in radian. Extending the above into 3-D,
$$\begin{equation}
\begin{bmatrix}x_1 \\ y_1 \\ z_1 \end{bmatrix}\begin{bmatrix}
    \cos(A_{\text{z}}) & -\sin(A_{\text{z}}) & 0 \\
    \sin(A_{\text{z}}) & \cos(A_{\text{z}}) & 0 \\
    0 & 0 & 1
\end{bmatrix}\begin{bmatrix}x_0 \\ y_0 \\ z_0 \end{bmatrix}
\end{equation}$$
CCW rotatioon seen from positive X asis is defined as
$$\begin{equation}\begin{bmatrix}y_1 \\ z_1\end{bmatrix}\begin{bmatrix}
\cos(A_{\text{x}}) & -\sin(A_{\text{x}}) \\
\sin(A_{\text{x}}) & \cos(A_{\text{x}})
\end{bmatrix}\begin{bmatrix}y_0 \\ z_0\end{bmatrix}
\end{equation}$$
, where $A_\text{x}$ is a rotatioin angle in radian. Extending the above into 3-D,
$$\begin{equation}\begin{bmatrix}x_1 \\ y_1 \\ z_1\end{bmatrix}\begin{bmatrix}
1 & 0 & 0 \\
0 & \cos(A_{\text{x}}) & -\sin(A_{\text{x}}) \\
0 & \sin(A_{\text{x}}) & \cos(A_{\text{x}})
\end{bmatrix}\begin{bmatrix}x_0 \\ y_0 \\ z_0\end{bmatrix}
\end{equation}$$
CCW rotation seen from positive Y axis is defined as
$$\begin{equation}\begin{bmatrix}z_1 \\ x_1\end{bmatrix}\begin{bmatrix}
\cos(A_\text{y}) & -\sin(A_\text{y}) \\
\sin(A_\text{y}) & \cos(A_\text{y}) \\
\end{bmatrix}\begin{bmatrix}z_0 \\ x_0\end{bmatrix}
\end{equation}$$
Swapping (row0 and row1) and (column0 and column1),
$$\begin{equation}\begin{bmatrix}x_1 \\ z_1\end{bmatrix}\begin{bmatrix}
\cos(A_\text{y}) & \sin(A_\text{y}) \\
-\sin(A_\text{y}) & \cos(A_\text{y}) \\
\end{bmatrix}\begin{bmatrix}x_0 \\ z_0\end{bmatrix}
\end{equation}$$
, where $A_\text{y}$ is a rotatioin angle in radian. Extending the above into 3-D,
$$\begin{equation}\begin{bmatrix}x_1 \\ y_1 \\ z_1\end{bmatrix}\begin{bmatrix}
\cos(A_\text{y}) & 0 & \sin(A_\text{y}) \\
0 & 1 & 0 \\
-\sin(A_\text{y}) & 0 & \cos(A_\text{y}) \\
\end{bmatrix}
\begin{bmatrix}x_0 \\ y_0 \\ z_0 \end{bmatrix}
\end{equation}$$
Arbitrary rotation in 3-D space is defined by a product of (2), (4), and (7),
$$\begin{equation}\begin{bmatrix}(2)\end{bmatrix}\begin{bmatrix}(4)\end{bmatrix}\begin{bmatrix}(7)\end{bmatrix} =
\begin{bmatrix}
c_\text{z}c_\text{y}-s_\text{z}s_\text{x}s_\text{y} && -s_\text{z}c_\text{x} && c_\text{z}s_\text{y}+s_\text{z}s_\text{x}c_\text{y} \\
s_\text{z}c_\text{y}+c_\text{z}s_\text{x}s_\text{y} && c_\text{z}c_\text{x} && s_\text{z}s_\text{y}-c_\text{z}s_\text{x}c_\text{y} \\
-c_\text{x}s_\text{y} && s_\text{x} && c_\text{x}c_\text{y}
\end{bmatrix}
\end{equation}$$
For homogenous coordinate, (8) is rewriten as
$$\begin{equation}\begin{bmatrix}
c_\text{z}c_\text{y}-s_\text{z}s_\text{x}s_\text{y} && -s_\text{z}c_\text{x} && c_\text{z}s_\text{y}+s_\text{z}s_\text{x}c_\text{y} && 0 \\
s_\text{z}c_\text{y}+c_\text{z}s_\text{x}s_\text{y} && c_\text{z}c_\text{x} && s_\text{z}s_\text{y}-c_\text{z}s_\text{x}c_\text{y} && 0 \\
-c_\text{x}s_\text{y} && s_\text{x} && c_\text{x}c_\text{y} && 0 \\
0 && 0 && 0 && 1
\end{bmatrix}\end{equation}$$
### __Linear Transform__
Linear transform is represented by a matrix
$$\begin{equation}\begin{bmatrix}
1 && 0 && 0 && x \\
0 && 1 && 0 && y \\
0 && 0 && 1 && z \\
0 && 0 && 0 && 1
\end{bmatrix}\end{equation}$$

The following functions are defined to create rotation transform matrices.
```
// homogeneous coordinate 3D rotation matrix around Z axis; i.e. in x-y -plane
SLC_<NTID>_t* SLC_TMat<NTID>_rotateZ(SLC_<NTID>_t c, SLC_<NTID>_t s, SLC_<NTID>_t* resut);
#define SLC_TMat<NTID>_rotateZrad(__rad, __result) \
    SLC_TMat<NTID>_rotateZ(SLC_cos<NTID>(__rad), SLC_sin<NTID>(__rad), __result)
#define SLC_TMat<NTID>_rotateZdeg(__deg, __result) \
    SLC_TMat<NT>_rotateZrad()
```
## Polar Coordinate and Cartesian Coordinate
A polar coordinate is represented by  
$r$ : a distance from the origin,  
$\theta$ : elevation angle from Z-plane,  
$\phi$ : azimuthal angle from X-axis,  
and the relationship between the polar coordinate and the cartesian coordinate is
$$\begin{equation}\begin{matrix}
x & = & r\cos(\theta)\cos(\phi) & = & r c_\theta c_\phi \\
y & = & r\cos(\theta)\sin(\phi) & = & r c_\theta s_\phi \\
z & = & r\sin(\theta) & = & r s_\theta\\
& & 1 &  = & {c_\theta}^2+{s_\theta}^2 \\
& & 1 & = & {c_\phi}^2+{s_\phi}^2
\end{matrix}\end{equation}$$
$$\begin{equation}
r = \sqrt(x^2+y^2+z^2)
\end{equation}$$
$$\begin{equation}
\cos(\theta) = \sqrt(x^2+y^2)/r, \sin(\theta)=z/r
\end{equation}$$
$$\begin{equation}
\cos(\phi)=x/\sqrt(x^2+y^2), \sin(\phi)=y/\sqrt(x^2+y^2)
\end{equation}$$

Getting the polar coordinate from the cartesian coordinate using Gauss-Newton method,
the objective function is

$$\begin{equation}\bold{F}(r,c_\theta, s_\theta, c_\phi, s_\phi) = \begin{bmatrix}
r c_\theta c_\phi - x \\
r c_\theta s_\phi - y \\
r s_\theta - z \\
{c_\theta}^2+{s_\theta}^2-1 \\
{c_\phi}^2+{s_\phi}^2-1 \\
\end{bmatrix} = \bold{0}
\end{equation}$$
Jacobian $\bold{J}$ is

$$\begin{equation}
\bold{J}=\begin{bmatrix}\frac{\partial\bold{F}}{\partial r} && \frac{\partial\bold{F}}{\partial c_\theta} && \frac{\partial\bold{F}}{\partial s_\theta} && \frac{\partial\bold{F}}{\partial c_\phi} && \frac{\partial\bold{F}}{\partial s_\phi} \end{bmatrix}\end{equation}$$

$$\begin{equation}
\frac{\partial\bold{F}}{\partial r} = \begin{bmatrix}
c_\theta c_\phi &
c_\theta s_\phi &
s_\theta & 0 & 0
\end{bmatrix}^t\end{equation}$$

$$\begin{equation}\frac{\partial\bold{F}}{\partial c_\theta} = \begin{bmatrix}r c_\phi & r s_\phi & 0 & 0 & 0
\end{bmatrix}^t\end{equation}$$

$$\begin{equation}\frac{\partial\bold{F}}{\partial s_\theta} = \begin{bmatrix}0 & 0 & r & 2 s_\theta & 0\end{bmatrix}^t\end{equation}$$

$$\begin{equation}
\frac{\partial\bold{F}}{\partial c_\phi} = \begin{bmatrix}
r c_\theta & 0 & 0 & 0 & 2c_\phi
\end{bmatrix}^t
\end{equation}$$

$$\begin{equation}
\frac{\partial\bold{F}}{\partial s_\phi} = \begin{bmatrix}
0 & r c_\theta & 0 & 0 & 2 s_\phi
\end{bmatrix}^t
\end{equation}$$

A struct is defined for polar coordinate.
```
typedef struct SLC_Polar<NTID> {
    SLC_<NTID>_t r, cphi, sphi, ctheta, stheta;
} SLC_Polar<NTID>_t, *SLC_PPolar<NTID>_t;
typedef const SLC_Polar<NTID>_t *SLC_PCPolar<NTID>_t;

void SLC_PolarFromCartesian<NTID>(SLC_PPolar<NTID>_t polar, const SLC_Pnt<NTID>_t cartesian);
void SLC_PolarToCartesian<NTID>(SLC_Pnt_t cartesian, SLC_PCPolar<NTID>_t polar);
```
## Line Properties
A line property is declared as
```
// A line and a plane can be represented by a point and a unit vector.
typedef struct {
    SLC_4<NTID>_t p0; // reference point
    SLC_4<NTID>_t v0; // a unit vector of line direction or plane normal
} SLC_LinePlane<NTID>_t, *SLC_PLinePlane<NTID>_t;
typedef const SLC_LinePlane<NTID>_t *SLC_PCLinePlane<NTID>_t;
```
, which is also used for a plane property and where `<NTID>` is `r32` or `r64`.
The line property can be determined by two points, __P__<sub>0</sub> and __P__<sub>1</sub> .
The reference point is __P__<sub>0</sub> and the unit direction vector is
(__P__<sub>1</sub> - __P__<sub>0</sub>)/|__P__<sub>1</sub> - __P__<sub>0</sub>|.

The API to get the line property is declared as
```
/*!
\brief Create a line object from two 3D points in homobeneous coordinate
\param line [out] line object
\param p0 [in] a point
\param p1 [in] another point
\return SLC_ESINGULAR if p0 and p1 are too close.
*/
SLC_errno_t SLC_Line<NTID>_Property
(SLC_PLinePlane<NTID>_t line, const SLC_Pnt<NTID>_t p0, const SLC_Pnt<NTID>_t p1);
```

## Plane Properties
A plane property is determined by three points, __P__<sub>0</sub>, __P__<sub>1</sub> and __P__<sub>2</sub> .
The plane normal is determined by cross-product of (__P__<sub>1</sub> - __P__<sub>0</sub>)
and (__P__<sub>2</sub> - __P__<sub>0</sub>). The reference point is __P__<sub>0</sub>.
The API to get the plane property is declared as
```
/*!
\brief Create a plane object from three 3D points in homobeneous coordinate
\param line [out] line object
\param p0 [in] a point
\param p1 [in] another point
\param p2 [in] 2nd another point
\return SLC_ESINGULAR if |(p1-p0)x(p2-p0)| is too small
*/
SLC_errno_t SLC_Plane<NTID>_Property
(SLC_PLinePlane<NTID>_t line, const SLC_Pnt<NTID>_t p0, const SLC_Pnt<NTID>_t p1, const SLC_Pnt<NTID>_t p2);
```