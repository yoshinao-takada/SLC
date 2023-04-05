#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_errno.h"
#include <stdlib.h>
#include <errno.h>

SLC_errno_t BaseUT(SLC_i32_t settings);
    SLC_errno_t SLC_NumbersUT(SLC_i32_t settings);
    SLC_errno_t SLC_NumbersCopyUT(SLC_i32_t settings);
    SLC_errno_t SLC_DLinkUT(SLC_i32_t settings);
SLC_errno_t ContainerUT(SLC_i32_t settings);
    SLC_errno_t SLC_ArrayUT(SLC_i32_t settings);
    SLC_errno_t SLC_RingBufferUT(SLC_i32_t settings);
SLC_errno_t MathUT(SLC_i32_t settings);
    SLC_errno_t SLC_MiniBLASUT(SLC_i32_t settings);
    SLC_errno_t SLC_MiniLAUT(SLC_i32_t settings);
    SLC_errno_t SLC_GeometryUT(SLC_i32_t settings);
    SLC_errno_t SLC_NLSLGNUT(SLC_i32_t settings);
SLC_errno_t IoDiagUT(SLC_i32_t settings);
    SLC_errno_t SLC_LogUT(SLC_i32_t settings);

int main()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_LogSink = stdout;
    do {
        SLC_test(err, BaseUT, 0, __func__, __LINE__);
        SLC_test(err, ContainerUT, 0, __func__, __LINE__);
        SLC_test(err, MathUT, 0, __func__, __LINE__);
        // SLC_test(err, IoDiagUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t BaseUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_NumbersUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_NumbersCopyUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_DLinkUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t ContainerUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_ArrayUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_RingBufferUT, 0, __func__, __LINE__);
    } while (0);
    return err;
}

SLC_errno_t MathUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_MiniBLASUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_MiniLAUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_GeometryUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_NLSLGNUT, 0, __func__, __LINE__);
    } while (0);
    return err;
}

// SLC_errno_t IoDiagUT(SLC_i32_t settings)
// {
//     SLC_errno_t err = EXIT_SUCCESS;
//     do {
//         SLC_test(err, SLC_LogUT, 0, __func__, __LINE__);
//     } while (0);
//     return err;
// }
