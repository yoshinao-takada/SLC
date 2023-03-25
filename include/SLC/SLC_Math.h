#include <math.h>
#include <complex.h>

#define SLC_r32deg2rad(__deg)  M_PIf * __deg / 180.0f
#define SLC_r64deg2rad(__deg)  M_PI * __deg / 180.0
#define SLC_r32cos(__a) cosf(__a)
#define SLC_r32sin(__a) sinf(__a)
#define SLC_r64cos(__a) cos(__a)
#define SLC_r64sin(__a) sin(__a)
#define SLC_c64cos(__a) ccosf(__a)
#define SLC_c64sin(__a) csinf(__a)
#define SLC_c128cos(__a) ccos(__a)
#define SLC_c128sin(__a) csin(__a)
#define SLC_r32sqrt(__a) sqrtf(__a)
#define SLC_r64sqrt(__a) sqrt(__a)
#define SLC_c64sqrt(__a) csqrtf(__a)
#define SLC_c128sqrt(__a) csqrt(__a)
