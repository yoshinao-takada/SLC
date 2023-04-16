# Line-Plane Crosssection
## Formulus
3D vector representations of line and plane are described in [Conceptual 3D Geometrical Structure](ConceptualStructure.md).  
Any point in a line is represented by
$$\begin{equation}
\bold{P} = \bold{P}_0 + A\bold{D}\text{.}
\end{equation}$$
Any point $\bold{P}$ in the plane with a reference point $\bold{P}_1$ is represented by
$$\begin{equation}
(\bold{P} - \bold{P}_1)\cdot\bold{N} = 0.
\end{equation}$$
Substituting $\bold{P}$ in Equation (1) in [Conceptual 3D Geometrical Structure](ConceptualStructure.md)
to the equation above,
$$\begin{equation}
(\bold{P}_0 + A\bold{D} - \bold{P}_1)\cdot\bold{N} = 0,
\end{equation}$$
where $A$ is determined as a unique value.
$$\begin{equation}
A_{\text{CROSS}} = {{(\bold{P}_1 - \bold{P}_0)\cdot\bold{N}}\over{\bold{D}\cdot\bold{N}}}.
\end{equation}$$
$\bold{P}$ in the line equation is uniquely determined as
$$\begin{equation}
\bold{P}_{CROSS} = \bold{P}_0 + A_{\text{CROSS}}\bold{D}.
\end{equation}$$
Note: It is impossible to get a reciprocal of $\bold{D}\cdot\bold{N}$ if the two vectors are orthogonal.

## API Definitions
The API is declared in `SLC_Geometry.h`.
```
// A line and a plane can be represented by a point and a unit vector.
typedef struct {
    SLC_4<NTID>_t p0; // reference point
    union {
        SLC_4<NTID>_t n0; // unit normal vector of a plane
        SLC_4<NTID>_t d0; // unit direction vector of a line
    } v;
} SLC_LinePlane<NTID>_t, *SLC_PLinePlane<NTID>_t;
typedef const SLC_LinePlane<NTID>_t *SLC_PCLinePlane<NTID>_t;

/*!
\brief Get a crosssection of a line and a plane.
\param line [in] reference point and direction vector of the line
\param plane [in] reference point and normal vector of the plane
\param cross [out] crosssection of the line and the plane
\return SLC_ESINGULAR(line and plane are parallel) or EXIT_SUCCESS
*/
SLC_errno_t SLC_LinePlane<NTID>_Crosssection(
    SLC_PCLinePlane<NTID>_t line, SLC_PCLiniePlane<NTID>_t plane, SLC_Pnt<NTID>_t cross);
```
## Unit Test for API
### Test 1: normal case
Plane:  
    __P__<sub>0</sub> = { 1.0, 0.5, -0.5, 1.0 }  
    __N__<sub>0</sub> = { 0.3, -0.3, 0.90555, 1.0 }
Line:
    __P__<sub>0</sub> = { 1.0, 1.0, 2.0, 1.0 }
    __D__<sub>0</sub> = { -0.3, 0.3, 0.90555, 1.0 }

### Test 2: plane and line are parallel
