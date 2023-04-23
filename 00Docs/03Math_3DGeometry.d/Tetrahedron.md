# Tetrahedron
## Objective
This document describes the ways of
1) Calculating mass-center of a tetrahedron,
2) Inserting a new vertex at the center of each edge.

## Mass-center
### Mass-center of equilateral triangle
Assuming an equilateral triangle with edges of 1.0 long.
Its height is equal to $\sqrt{1 - {1\over{4}}}$ = $\sqrt{3}\over{2}$
Assuming the center of the bottom edge is at the origin, the coordinates of the three vertices in 3D-space are
$$\begin{equation}\begin{matrix}
\bold{P}_{0} & = & (-0.5, 0) \\
\bold{P}_{1} & = & (+0.5, 0) \\
\bold{P}_{2} & = & (0, {\sqrt{3}\over{2}}) \\
\end{matrix}\end{equation}$$
Mass-center coordinate $\bold{P}$ satisfies the conditions,
$$\begin{equation}\begin{matrix}
|\bold{P} - \bold{P}_{0}|^2 & = & |\bold{P} - \bold{P}_{1}|^2 , \\
|\bold{P} - \bold{P}_{1}|^2 & = & |\bold{P} - \bold{P}_{2}|^2 , \\
|\bold{P} - \bold{P}_{2}|^2 & = & |\bold{P} - \bold{P}_{0}|^2 . \\
\end{matrix}\end{equation}$$
Expanding them,
$$\begin{equation}\begin{matrix}
(p_x - p_{0x})^2 + (p_y - p_{0y})^2 & = &
    (p_x - p_{1x})^2 + (p_y - p_{1y})^2 \\
(p_x - p_{1x})^2 + (p_y - p_{1y})^2 & = &
    (p_x - p_{2x})^2 + (p_y - p_{2y})^2 \\
(p_x - p_{2x})^2 + (p_y - p_{2y})^2 & = &
    (p_x - p_{0x})^2 + (p_y - p_{0y})^2 \\
\end{matrix}\end{equation}$$
The triangle is symmetrical and $p_{x} = 0$ is obvious. And the considering only
the third equation in (3) and applying (1),
$$\begin{equation}
{p_y}^2 - 2{p_y}{p_{2y}} + {p_{2y}}^2 = 
    {p_{0x}}^2 + {p_y}^2 - 2{p_y}{p_{0y}} + {p_{0y}}^2
\end{equation}$$
Vanishing zero terms,
$$\begin{equation}
-2{p_y}{p_{2y}} + {p_{2y}}^2 = 
    {p_{0x}}^2
\end{equation}$$
$$\begin{equation}\begin{matrix}
p_y  & = & {{p_{2y}}^2 - {{p_{0x}}^2}\over{2p_{2y}}} \\
 & = & {(3/4) - (1/4)}\over{\sqrt{3}} \\
 & = & 1\over{2\sqrt{3}}
\end{matrix}\end{equation}$$
The mass-center of the equilateral triangle is (0, $1\over{2\sqrt{3}}$)
### Mass-center of tetrahedron
Assuming an equilateral triangle of
1) edge length = 1,
2) normal vector is aligned to Z-axis,
3) one of three edges is parallel to X-axis,
4) the mass-center of the triangle is at (0, 0, 0),

Considering [the mass-center of an equilateral](#mass-center-of-equilateral-triangle) triangle, the corner coordinates of the triangle are  
__P__<sub>0</sub> = (-0.5, $1\over{2\sqrt{3}}$, 0),  
__P__<sub>1</sub> = (0.5, $1\over{2\sqrt{3}}$, 0),  
__P__<sub>2</sub> = (0, -$1\over{\sqrt{3}}$, 0) <br/>
The top vertex __P__<sub>3</sub>(0, 0, _p_<sub>3z</sub>) of the tetrahedron satisfies,
$$\begin{equation}
{p_{3z}}^2 + {1\over{3}} = 1 ,
\end{equation}$$
$$\begin{equation}
{p_{3z}} = \sqrt{{2}\over{3}} .
\end{equation}$$
The top vertex is
__P__<sub>3</sub> = (0, 0, $\sqrt{{2}\over{3}}$). <br/>
The mass center coordinate $\bold{P} = (0, 0, p_z)$ satisfies
$$\begin{equation}
|\bold{P} - \bold{P}_0|^2 = |\bold{P} - \bold{P}_1|^2 =
|\bold{P} - \bold{P}_2|^2 = |\bold{P} - \bold{P}_3|^2.
\end{equation}$$
__P__<sub>0</sub> through __P__<sub>2</sub> are obviously symmetrical around __P__ .
Therefore considering only __P__<sub>2</sub> and __P__<sub>3</sub>.
$$\begin{equation}
p_x^2 + (p_y - p_{2y})^2 + p_z^2 = p_x^2 + p_y^2 + (p_z - p_{3z})^2 ,
\end{equation}$$
Vanishing null terms,
$$\begin{equation}
{p_{2y}}^2 = -2p_zp_{3z} + {p_{3z}}^2 ,
\end{equation}$$
$$\begin{equation}\begin{matrix}
p_z & = & {{{p_{3z}}^2 - {{p_{2y}}}^2}\over{2p_{3z}}} \\
 & = & {(2/3) - (1/3)} \over {2\sqrt{2/3}} \\
 & = & {1 \over {2\sqrt{6}}} . \\
\end{matrix}\end{equation}$$
Moving the tetrahedron, its vertices are<br/>
__P__<sub>0</sub> = (-0.5, $1\over{2\sqrt{3}}$, $-{1\over{2\sqrt{6}}}$), <br/>
__P__<sub>1</sub> = (0.5, $1\over{2\sqrt{3}}$, $-{1\over{2\sqrt{6}}}$), <br/>
__P__<sub>2</sub> = (0, -$1\over{\sqrt{3}}$, $-{1\over{2\sqrt{6}}}$) <br/>
__P__<sub>3</sub> = (0, 0, $\sqrt{3}\over{2\sqrt{2}}$)<br/>
## Inserting new vertices
