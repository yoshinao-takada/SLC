# Conceptual 3D Geometrical Structure
There are many concept in 3D geometry but only several concepts are defined here.

Table 1. Geometrical Concepts
Name | Description
-----|------------
Line | Linear line
Plane | Plane
<br/>

## Line
A line is represented by a point $\bold{P}_0$ and a direction vector $\bold{D}$ ($|\bold{D}| = 1$).  
An arbitrary point 
$\bold{P}$ in the line and an arbitrary number $A$ have a relationship,
$$\begin{equation}
\bold{P} = \bold{P}_0 + A\bold{D}\text{.}
\end{equation}$$

## Plane
A plane is represented by a point $\bold{P}_0$ and a normal vector $\bold{N}$ ($|\bold{N}| = 1$).  
An arbitrary point $\bold{P}$ in the plane satisfies
$$\begin{equation}
(\bold{P} - \bold{P}_0)\cdot\bold{N} = 0.
\end{equation}$$

## Data Structure and API
A line is represented by a point and a unit direction vector.
A plane is reprenseted by a point and a unit normal vector.
They can be represented by points and unit vectors as
```
typedef struct {
    SLC_4<NTID>_t p0; // reference point
    union {
        SLC_4<NTID>_t n0; // unit normal vector of a plane
        SLC_4<NTID>_t d0; // unit direction vector of a line
    } v;
} SLC_LinePlane<NTID>_t, *SLC_PLinePlane<NTID>_t;
typedef const SLC_LinePlane<NTID>_t *SLC_PCLinePlane<NTID>_t;

/*!
\brief Return true if pnt is in line.
\param line [in] reference line
\param pnt [in] target point to discriminate.
\param tol [in] criteria to discriminate an inner product of two unit vectors is nearly equal to 1 or not.
\return true: pnt is in line, false: pnt is NOT in line.
*/
SLC_bool_t SLC_Line<NTID>_IsIn(SLC_PCLinePLane<NTID>_t line, SLC_Pnt<NTID>_t pnt, SLC_<NTID>_t tol);

// Return true if pnt is in plane. tol is a criteria in discriminating two unit vector product is
// nearly equal to 0 or not.
/*!
\brief Return false if pnt is not in plane.
\param plane [in] reference plane
\param pnt [in] target point to discriminate
\param tol [in] criteria to discriminate an inner product of two unit vectors is nearly equal to 0 or not.
\return true: pnt is in line, false: pnt is NOT in line.
*/
SLC_bool_t SLC_Plane<NTID>_IsIn(SLC_PCLinePLane<NTID>_t plane, SLC_Pnt<NTID>_t pnt, SLC_<NTID>_t tol);
```