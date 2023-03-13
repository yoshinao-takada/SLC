# Line-Plane Crosssection
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
A_{CROSS} = {{(\bold{P}_1 - \bold{P}_0)\cdot\bold{N}}\over{\bold{D}\cdot\bold{N}}}.
\end{equation}$$
$\bold{P}$ in the line equation is uniquely determined as
$$\begin{equation}
\bold{P}_{CROSS} = \bold{P}_0 + A_{CROSS}\bold{D}.
\end{equation}$$

