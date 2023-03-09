# Nonlinear Solver (NLSL)
## Overview
Two types of NLSL are defined.
* Gauss-Newton method: applicable only to differentiable functions.
* Nelder-Mead method: applicable to any continuous functions including spline functions like broken-line.

## Generalized Nonlinear Vector-Vector Function
```
typedef SLC_errno_t (*SLC_GVVF_<NTID>)(
    SLC_<NTID>_t* y, SLC_size_t cy, /* depedent variables */
    const SLC_<NTID>_t* x, SLC_size_t cx, /* dependent variables */
    const SLC_<NTID>_t* c, SLC_size_t cc /* constants */);
```

## Gauss-Newton Method
I thought that the most understandable formulation is presented in a topic,
**"_k_ variables, _k_ functions"** and
**"_k_ variables, _m_ equations, with _m_&nbsp;&gt;&nbsp;_k_"** in
[a Wikipedia article](https://en.wikipedia.org/wiki/Newton%27s_method).

Details are described in [README-gaussnewton.md](README-gaussnewton.md)

## Nelder-Mead method