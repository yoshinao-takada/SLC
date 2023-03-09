# Callable objects
The callable objects and function pointer types are defined in `SLC_Callable.c/.h`

Function pointers are defined as follows.
```
typedef void (*SLC_Func0)(SLC_i32_t* result, void* arg);
typedef void (*SLC_Func1)(SLC_i32_t* result, const void* arg0, void* arg1);

typedef struct {
    SLC_Func0 func;
    void* arg;
    SLC_i32_t result;
    SLC_i32_t reserved;
} SLC_Callable0_t, *SLC_PCallable0_t;

typedef struct {
    SLC_Func1 func;
    void* arg0;
    void* arg1;
    SLC_i32_t result;
    SLC_i32_t reserved;
} SLC_Callable1_t, *SLC_PCallable1_t;

void SLC_Callable_Execute0(SLC_PCallable0_t callable);
void SLC_Callable_Execute1(SLC_PCallable1_t callable);
```
