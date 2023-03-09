# Overview
`SLC` is a small library for C consisting of groups listed in Table 1.  
Identifiers defined in each group has a prefix listed in  the table.
The prefixes and main bodies of identifiers are separated by an underscore character, '`_`'.  
<br/>

Table 1. Library groups
Directory | Description
----------|--------
01Base    |  Small data structures, functions, and macros<br/>as basis of other groups.
02Container | 1-D, 2-D, 3-D arrays of various element types,<br/>linked list and its descendents with special functions,<br/>ring buffers, etc.
03Math   |  Polynomials, Linear algebraic functions,<br/> Linear and non-linear simultaneous equation solvers<br/> of various number types,
04Control |  Single layer finite state machine, Hierarchical finite state machine, <br/>easy to use wrapper for thread and timer, single thread scheduler
05IoDiag |  1) I/O and diagnostics utility functions, <br/>2) utility functions treating process, files, and directories,
<br/>

Table 2. Links to detailed documents
Group  | Detailed item | Link
-------|---------------|-----------
Base   | Small data structure | [01Base_SmallData.md](01Base_SmallData.md)
Base   | Doubly linked list base | [01Base_DLink.md](01Base_DLink.md)
Base   | Callable object | [01Base_Callable.md](01Base_Callable.md)
Container | Array | [02Container_Array.md](02Container_Array.md)
Container | Ring buffer | [02Container_RingBuffer.md](02Container_RingBuffer.md)
Container | Dictionary | [02Container_Dictionary.md](02Container_Dictionary.md)
Math | CodeGen | [03Math_CodeGen.md](03Math_CodeGen.md)
Math | Polynomial | [03Math_Polynomial.md](03Math_Polynomial.md)
Math | Mini BLAS | [03Math_MiniBLAS.md](03Math_MiniBLAS.md)
Math | Mini LA   | [03Math_MiniLA.md](03Math_MiniLA.md)
Math | Nonlinear solver | [03Math_NLSL.md](03Math_NLSL.md)
Math | 3D vector geometry | [03Math_3DGeometry.md](03Math_3DGeometry.md)
Math | Linear circuit | [03Math_LinearCircuit.md](03Math_LinearCircuit.md)
Control | FSM | [04Control_FSM.md](04Control_FSM.md)
Control | HSM | [04Control_HSM.md](04Control_HSM.md)
Control | Event | [04Control_Event.md](04Control_Event.md)
Control | Scheduler | [04Control_Scheduler.md](04Control_Scheduler.md)
IoDaig  | Log | [05IoDiag_LogAndMeasure.md](05IoDiag_LogAndMeasure.md)
IoDaig  | Conditional branch | [05IoDiag_ConditionalBranch.md](05IoDiag_ConditionalBranch.md)
IoDaig  | Process | [05IoDiag_Process.md](05IoDiag_Process.md)