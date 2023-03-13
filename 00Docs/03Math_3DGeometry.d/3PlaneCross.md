# Three Plane Crosssection
Any point $\bold{P}$ in a plane with
a reference point $\bold{P}_0$ and a normal vector $\bold{N}_0$ is represented by
$$\begin{equation}
(\bold{P} - \bold{P}_0)\cdot\bold{N}_0 = 0\text{.}
\end{equation}$$
Organize the equation for $\bold{P}$ with three planes (0, 1, 2), 
$$\begin{equation}\begin{matrix}
\bold{P}\cdot\bold{N}_0 && = && \bold{P}_0\cdot\bold{N}_0\text{,} \\
\bold{P}\cdot\bold{N}_1 && = && \bold{P}_1\cdot\bold{N}_1\text{,} \\
\bold{P}\cdot\bold{N}_2 && = && \bold{P}_2\cdot\bold{N}_2\text{.} \\
\end{matrix}\end{equation}$$
Organize them in a matrix formula,
$$\begin{equation}
\begin{bmatrix}
n_{0x} && n_{0y} && n_{0z} \\
n_{1x} && n_{1y} && n_{1z} \\
n_{2x} && n_{2y} && n_{2z}
\end{bmatrix}\begin{bmatrix} x \\ y \\ z \end{bmatrix} = \begin{bmatrix}
\bold{P}_0\cdot\bold{N}_0 \\ \bold{P}_1\cdot\bold{N}_1 \\ \bold{P}_2\cdot\bold{N}_2
\end{bmatrix}
\end{equation}$$
Solving (3), a unique point is determined and it is the crosssection of the three planes.