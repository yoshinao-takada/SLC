#if !defined(_SLC_ERRNO_H)
#define _SLC_ERRNO_H
#include "SLC/SLC_Numbers.h"
typedef SLC_i32_t SLC_errno_t;
#define SLC_ESINGULAR   0x10000 /* matrix is near singular */
#define SLC_ENOCONV     0x10001 /* not converged within iteration limit */
#define SLC_EMATSIZE    0x10002 /* Matrix size mismatch */
#define SLC_EINVAL      0x10003 /* Invalid operation (usually in objective function or Jacobian) */
#endif