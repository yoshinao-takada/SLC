#include "SLC/SLC_Array.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_errno.h"
#define ARRAY_UNIT_SIZE 5
#define ARRAY_1D_ELEMENTCOUNT   10
#define EXPECTED_CONTROL    { ARRAY_UNIT_SIZE, ARRAY_1D_ELEMENTCOUNT, 1, 1 }
static const SLC_4i16_t _expected_control = EXPECTED_CONTROL;
static SLC_PArray_t array = NULL;

#define ARE_EQUAL_4i16(__a, __b) ((__a[0] == __b[0]) &&(__a[1] == __b[1]) &&(__a[2] == __b[2]) &&(__a[3] == __b[3]))

SLC_errno_t SLC_ArrayUTScenario(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        if (!ARE_EQUAL_4i16(_expected_control, array->cont.i16))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in initializing array @ %s, %d\n", __func__, __LINE__);
            SLC_LogERR(err, "array->cont = {%d, %d, %d, %d}\n", 
                array->cont.i16[0], array->cont.i16[1], array->cont.i16[2], array->cont.i16[3]);
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_ArrayUTWithHeap(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    array = SLC_Array_Calloc(ARRAY_1D_ELEMENTCOUNT, ARRAY_UNIT_SIZE);
    do {
        SLC_test(err, SLC_ArrayUTScenario, settings, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    free(array);
    return err;
}

SLC_errno_t SLC_ArrayUTWithStackframe(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    array = SLC_Array_Calloca(ARRAY_1D_ELEMENTCOUNT, ARRAY_UNIT_SIZE);
    do {
        SLC_test(err, SLC_ArrayUTScenario, settings, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_ArrayUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_ArrayUTWithHeap, settings, __func__, __LINE__);
        SLC_test(err, SLC_ArrayUTWithStackframe, settings, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}