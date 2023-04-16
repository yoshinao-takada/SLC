# Two-Plane crosssection
## Formulation
A line exists as a crosssection of two planes p<sub>0</sub>, p<sub>1</sub> if the planes are not parallel.
$$\begin{equation}\begin{matrix}
(\bold{P} - \bold{P}_0)\cdot\bold{N}_0 && = && 0\text{,} \\
(\bold{P} - \bold{P}_1)\cdot\bold{N}_1 && = && 0\text{,} \\
\end{matrix}\end{equation}$$
where
$$\begin{equation}
\bold{P} = \bold{P}_2 + A(\bold{N}_0\times\bold{N}_1)\text{.}
\end{equation}$$
The direction of the line is determined by the cross-product of the normal vectors of the planes.  
$\bold{P}_2$ is unknown right now.
By the way, we can assume the third plane which is paralle to neither p<sub>0</sub> nor p<sub>1</sub>
with the reference point $\bold{P}_0$ and the normal vector $\bold{N}_0\times\bold{N}_1$.
The plane is represented by
$$\begin{equation}
(\bold{P}-\bold{P}_0)\cdot(\bold{N}_0\times\bold{N}_1) = 0
\end{equation}$$
The crosssection point of the three planes can be derived from (1) and (3).
Substituting the point to $\bold{P}_2$ in (2), the crosssection line is determined.

## API Definition
The API is declared in `SLC_Geometry.h`
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
\brief Crosssection of three planes
\param planes [in]
\param cross [out]
\return SLC_ESINGULAR (two of three planes are near parallel) or EXIT_SUCCESS.
*/
SLC_errno_t SLC_Plane<NTID>_2Crosssection(SLC_PCLinePlane<NTID>_t planes, SLC_PLinePlane<NTID>_t cross);
```