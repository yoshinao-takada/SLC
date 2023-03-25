#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_Log.h"
#include "SLC/SLC_errno.h"

static const SLC_16r32_t src_r32 = 
{
    -1.0f, -0.9f, -0.8f, -0.7f,
    -0.6f, -0.5f, -0.4f, -0.3f,
    -0.2f, -0.1f, 0.0f, 0.1f,
    0.2f, 0.3f, 0.4f, 0.5f
};

SLC_errno_t SLC_NumbersUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_16r32_t dst_r32;
    do {
        SLC_COPY4(dst_r32, src_r32);
        for (SLC_size_t i = 0; i < 4; i++)
        {
            if (!SLC_r32_areequal(src_r32[i], dst_r32[i], 1.0e-5f))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_COPY4 @ %s,%d\n", __func__, __LINE__);
            }
        }

        SLC_COPY8(dst_r32, src_r32);
        for (SLC_size_t i = 0; i < 8; i++)
        {
            if (!SLC_r32_areequal(src_r32[i], dst_r32[i], 1.0e-5f))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_COPY8 @ %s,%d\n", __func__, __LINE__);
            }
        }

        SLC_COPY16(dst_r32, src_r32);
        for (SLC_size_t i = 0; i < 16; i++)
        {
            if (!SLC_r32_areequal(src_r32[i], dst_r32[i], 1.0e-5f))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_COPY16 @ %s,%d\n", __func__, __LINE__);
            }
        }
    } while(0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}