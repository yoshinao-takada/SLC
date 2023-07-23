# 3D Analyzer: Sphere

## Overview
A point $\textbf{P} = (x, y, z)$ is transformed by a translation (-d<sub>X</sub>, -d<sub>Y</sub>, -d<sub>Z</sub>)
and a scaling (s, s, s) to a point $\textbf{Q}$ on the unit sphere. The transformation is represented by
$$\begin{equation}
\textbf{Q} = \{s(x - X_\text{t}), s(y - Y_\text{t}), s(z - Y_\text{t})\}
\end{equation}$$
if $\textbf{Q}$ is on the unit sphere, 
$$\begin{equation}
\textbf{Q}\cdot{\textbf{Q}}-1 = 0
\end{equation}$$
Expanding the equation,
$$\begin{equation}
s^2\{(x-X_\text{t})^2+(y-Y_\text{t})^2+(z-Z_\text{t})^2\}-1 = 0
\end{equation}$$
$$\begin{equation}
e^2 = \Sigma_{i=0}^{N-1}\{{\textbf{Q}_i}\cdot{\textbf{Q}_i}-1\}^2
\end{equation}$$
is minimized with the best transformation.
$$\begin{equation}
\frac{d{e^2}}{ds}=0
\end{equation}$$
$$\begin{equation}
\frac{d{e^2}}{dX_\text{t}}=0
\end{equation}$$
$$\begin{equation}
\frac{d{e^2}}{dY_\text{t}}=0
\end{equation}$$
$$\begin{equation}
\frac{d{e^2}}{dZ_\text{t}}=0
\end{equation}$$

expanding (15),
$$\begin{equation}
\frac{d{e^2}}{ds}=4s\Sigma_{i=0}^{N-1}\{{\textbf{Q}_i}\cdot{\textbf{Q}_i}-1\}
    \{(x_i-X_\text{t})^2+(y_i-Y_\text{t})^2+(z_i-Z_\text{t})^2\} = 0
\end{equation}$$

expanding (16),
$$\begin{equation}
\frac{d{e^2}}{dX_\text{t}}=-4s^2\Sigma_{i=0}^{N-1}\{{\textbf{Q}_i}\cdot{\textbf{Q}_i}-1\}
    (x_i - X_\text{t})
\end{equation}$$

expanding (17),
$$\begin{equation}
\frac{d{e^2}}{dY_\text{t}}=-4s^2\Sigma_{i=0}^{N-1}\{{\textbf{Q}_i}\cdot{\textbf{Q}_i}-1\}
    (y_i - Y_\text{t})
\end{equation}$$

expanding (18),
$$\begin{equation}
\frac{d{e^2}}{dZ_\text{t}}=-4s^2\Sigma_{i=0}^{N-1}\{{\textbf{Q}_i}\cdot{\textbf{Q}_i}-1\}
    (z_i - Z_\text{t})
\end{equation}$$
