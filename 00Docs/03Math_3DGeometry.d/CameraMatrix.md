# Camera Matrix Formulation
A camera matrix consists of three components,  
1) rotation around view-line,
2) rotation from negative z-axis to view-line direction,
3) moving from origin to the camera position.
The transform matrices are applied in order of 1), 2), and 3).

## Rotation around view-line
The rotation matrix is that of around z-axis. Its property is given by a rotation angle
or its cosine and sine.
$$\begin{equation}\begin{bmatrix}
c_\psi & -s_\psi & 0 & 0 \\ s_\psi & c_\psi & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1
\end{bmatrix}\end{equation}$$
## Rotation from negative z-axis to view-line direction
The view-line direction vector is given by the camera position __P__<sub>0</sub> and the point
where the camera look at, __P__<sub>1</sub>.
The direction vector is <br/>__D__ = (__P__<sub>1</sub> - __P__<sub>0</sub>) / |__P__<sub>1</sub> - __P__<sub>0</sub>|  
Considering a polar coordinate system with y-axis as poles,
__D__ in the polar representation is  
{ _r_, _c_<sub>&phi;</sub>, _s_<sub>&phi;</sub>, _c_<sub>&theta;</sub>, _s_<sub>&theta;</sub>} = 
{ 1.0, D<sub>Z</sub> / |__D__<sub>H</sub>| , D<sub>Z</sub> / |__D__<sub>H</sub>|, D<sub>Y</sub> / |__D__|, |__D__<sub>H</sub>| / |__D__|},  
where |__D__<sub>H</sub>| = sqrt(1 - D<sub>Y</sub><sup>2</sup>).  
The rotation matrix transforming z-axis to __D__ is  
$$\begin{equation}\begin{bmatrix}
c_\phi & 0 & s_\phi & 0 \\ 0 & 1 & 0 & 0 \\ -s_\phi & 0 & c_\phi & 0 \\ 0 & 0 & 0 & 1
\end{bmatrix}\begin{bmatrix}
1 & 0 & 0 & 0 \\ 0 & c_\theta & -s_\theta & 0 \\ 0 & s_\theta & c_\theta & 0 \\ 0 & 0 & 0 & 1
\end{bmatrix} ,\end{equation}$$
where a rotation around x-axis is firstly applied and a rotation around y-axis is secondly applied.
## Moving from origin to the camera position (X<sub>C</sub>, Y<sub>C</sub>, Z<sub>C</sub>)
$$\begin{equation}\begin{bmatrix}
1 & 0 & 0 & X_C \\
0 & 1 & 0 & Y_C \\
0 & 0 & 1 & Z_C \\
0 & 0 & 0 & 1
\end{bmatrix}\end{equation}$$

## Scaling in Orthnormal Mode
In orthnormal mode, the camera look toward negative Z-axis direction.
* [_Z_<sub>FAR</sub> , _Z_<sub>NEAR</sub>] is mapped to [-1, 1].
* [-_W_ / 2, _W_ / 2] is mapped to [-1, 1]
* [-_H_ / 2, _H_ / 2] is mapped to [-1, 1],  
where _W_ is a width of a viewbox, _H_ is a height of a viewbox, and
[_Z_<sub>MIN</sub> , _Z_<sub>MAX</sub>] is a depth range of a viewbox.
The transform matrix is
$$\begin{equation}\begin{bmatrix}
2/W & 0 & 0 & 0 \\ 0 & 2/H & 0 & 0 \\ 0 & 0 & 2/(Z_{NEAR} - Z_{FAR}) & -(Z_{NEAR} + Z_{FAR})/2 \\
0 & 0 & 0 & 1
\end{bmatrix}\end{equation}$$

## Scaling in Perspective Mode
In perspective mode, a frustum is mapped to the canonical viewbox.
* [_Z_<sub>MIN</sub> , _Z_<sub>MAX</sub>] is mapped to [-1, 1].
* _X_(_Z_ = 1) = _W_ / 2
* _Y_(_Z_ = 1) = _H_ / 2
$$\begin{equation}
\begin{bmatrix}
2 / W & 0 & 0 & 0 \\ 0 & 2 / H & 0 & 0 \\
0 & 0 & a & b \\ 0 & 0 & -1 & 0
\end{bmatrix}
\end{equation}$$
$a$ and $b$ satisfies
$$\begin{equation}\begin{matrix}
1 & = & a + b/Z_{NEAR} \\
-1 & = & a + b/Z_{FAR}
\end{matrix}\end{equation}$$
$$\begin{equation}\begin{bmatrix}1 \\ -1 \end{bmatrix} =
\begin{bmatrix}1 & 1/Z_{NEAR} \\ 1 & 1/Z_{FAR}\end{bmatrix}
\begin{bmatrix}a \\ b\end{bmatrix}
\end{equation}$$
$$\begin{equation}
a = {{Z_{FAR} + Z_{NEAR}}\over{Z_{NEAR} - Z_{FAR}}}
\end{equation}$$
$$\begin{equation}
b = -{{2Z_{FAR}Z_{NEAR}}\over{Z_{NEAR}-Z_{FAR}}}
\end{equation}$$
## API
```
// create a camera position matrix
typedef struct {
    SLC_4<NTID>_t cameraIsAt;
    SLC_4<NTID>_t lookAt;
    SLC_2<NTID>_t viewAxisRotationCosSin;
} SLC_CameraPosition<NTID>_t, *SLC_PCameraPosition<NTID>_t;
typedef const SLC_CameraPosition<NTID>_t *SLC_PCCameraPosition<NTID>_t;

// create a camera opsition matrix.
// It transforms 
// object vertex coordinates in world coordinate system
// to those in camera coordinate system.
// It is the inverse of camera position coordinate and attitude in the world coordinate system.
const SLC_<NTID>_t* SLC_Camera<NTID>_Position(SLC_PCCameraPosition<NTID>_t pos, SLC_TMat<NTID>_t work);

typedef struct {
    SLC_2<NTID>_t width_height;
    SLC_2<NTID>_t far_near; // far: negative larger number, near: usually negative smaller number
} SLC_Projection<NTID>_t, *SLC_PProjection<NTID>_t;
typedef const SLC_Projection<NTID>_t *SLC_PCProjection<NTID>_t;


// create a camera projection matrix of orthnormal mode
const SLC_<NTID>_t* SLC_Camera<NTID>_Orth(
    SLC_PCProjection<NTID>_t projconf,
    SLC_TMat<NTID>_t work);

// create a camera projection matrix of perspective mode
const SLC_<NTID>_t* SLC_Camera<NTID>_Perspective(
    SLC_PCProjection<NTID>_t projconf,
    SLC_TMat<NTID>_t work);

```
## Unit Tests
### __Polar-Y Cartesian Conversion__
x-, y-, z-axes direction vectors are converted to polar-Y coordinates and restored.  
x-axis: [1,0,0,1] => { R=1, C<sub>phi</sub>=0, S<sub>phi</sub>=1, C<sub>theta</sub>=1, S<sub>theta</sub>=0 }  
y-axis: [0.0001,1,0,1] => { R=1, C<sub>phi</sub>=0, S<sub>phi</sub>=1, C<sub>theta</sub>=0, S<sub>theta</sub>=1 }  
z-axis: [0,0,1,1] => { R=1, C<sub>phi</sub>=1, S<sub>phi</sub>=0, C<sub>theta</sub>=1, S<sub>theta</sub>=0 }  

### __View Line Rotation__
Two points are given.  
__P__<sub>C0</sub>: camera origin in the world cooridnate system  
__P__<sub>OBJ</sub>: a point seen by the camera  
__M__: A transform matrix obtained by `SLC_Camera<NTID>_CameraDirection` from the points.  
__M__<sup>-1</sup>: transforms __P__<sub>C0</sub> to the origin, and transforms __P__<sub>OBJ</sub>
to a point on Z-axis in negative region. The distance between the transformed points are equal to
that of their orignal points.

### __Orth-Normal Mode Projection__
Several combinations of _Z_<sub>FAR</sub>, _Z_<sub>NEAR</sub>, _W_, and _H_ are given by random number
generator.  
[_W_, 0, _Z_<sub>AVE</sub>, 1] => [1, 0, 0, 1]  
[-_W_, 0, _Z_<sub>AVE</sub>, 1] => [-1, 0, 0, 1]  
[0, _H_, _Z_<sub>AVE</sub>, 1] => [0, 1, 0, 1]  
[0, -_H_, _Z_<sub>AVE</sub>, 1] => [0, -1, 0, 1]  
[0, 0, _Z_<sub>NEAR</sub>, 1] => [0, 0, 1, 1]  
[0, 0, _Z_<sub>FAR</sub>, 1] => [0, 0, -1, 1]  
where  
_Z_<sub>AVE</sub> = (_Z_<sub>NEAR</sub> + _Z_<sub>FAR</sub>)/2  

### __Perspective Mode Projection__
Several combinations of _Z_<sub>FAR</sub>, _Z_<sub>NEAR</sub>, _W_, and _H_ are given by random number
generator.  
[_W_, 0, _Z_<sub>NEAR</sub>, 1] => [_w_, 0, _w_, _w_], where _w_ is any number.  
[-_W_, 0, _Z_<sub>NEAR</sub>, 1] => [-_w_, 0, _w_, _w_], where _w_ is any number.  
[0, _H_, _Z_<sub>NEAR</sub>, 1] => [0, _w_, _w_, _w_], where _w_ is any number.  
[0, -_H_, _Z_<sub>NEAR</sub>, 1] => [0, _w_, _w_, _w_], where _w_ is any number.  
[0, 0, _Z_<sub>NEAR</sub>, 1] => [0, 0, _w_, _w_], where _w_ is any number.  
<br/>
[_W_, 0, _Z_<sub>FAR</sub>, 1] => [_w_, 0, -_w_, _w_], where _w_ is any number.  
[-_W_, 0, _Z_<sub>FAR</sub>, 1] => [-_w_, 0, -_w_, _w_], where _w_ is any number.  
[0, _H_, _Z_<sub>FAR</sub>, 1] => [0, _w_, -_w_, _w_], where _w_ is any number.  
[0, -_H_, _Z_<sub>FAR</sub>, 1] => [0, _w_, -_w_, _w_], where _w_ is any number.  
[0, 0, _Z_<sub>FAR</sub>, 1] => [0, 0, -_w_, _w_], where _w_ is any number.