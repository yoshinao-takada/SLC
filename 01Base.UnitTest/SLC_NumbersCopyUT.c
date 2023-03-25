#include "SLC/SLC_NumbersCopy.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <assert.h>

#pragma region SLC_NumbersCopyUT_with_number_type_SLC_r32_t.
SLC_errno_t SLC_r32_copyUT(SLC_i32_t settings)
{
    SLC_r32_t src[] = { SLC_r32_rand, SLC_r32_rand, SLC_r32_rand, SLC_r32_rand };
    SLC_r32_t dst[SLC_ARRAYSIZE(src)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r32_copy(dst, 1, src, 1, SLC_ARRAYSIZE(src));
        if (SLC_ARRAYSIZE(src) != 4)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in SLC_ARRAYSIZE() @ %s,%d\n", __func__, __LINE__);
            break;
        }
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (src[i] != dst[i])
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r32_copy() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_set0UT(SLC_i32_t settings)
{
    SLC_r32_t src[] = { SLC_r32_rand, SLC_r32_rand, SLC_r32_rand, SLC_r32_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r32_set0(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_r32_areequal(src[i], SLC_r32_units[0], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r32_set0() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_set1UT(SLC_i32_t settings)
{
    SLC_r32_t src[] = { SLC_r32_rand, SLC_r32_rand, SLC_r32_rand, SLC_r32_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r32_set1(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_r32_areequal(src[i], SLC_r32_units[1], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r32_set1() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_swapUT(SLC_i32_t settings)
{
    SLC_r32_t src0[] = { SLC_r32_rand, SLC_r32_rand, SLC_r32_rand, SLC_r32_rand };
    SLC_r32_t src1[] = { SLC_r32_rand, SLC_r32_rand, SLC_r32_rand, SLC_r32_rand };
    SLC_r32_t src0_backup[SLC_ARRAYSIZE(src0)], src1_backup[SLC_ARRAYSIZE(src1)];
    SLC_r32_t swapbuffer[SLC_ARRAYSIZE(src0)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r32_copy(src0_backup, 1, src0, 1, SLC_ARRAYSIZE(src0));
        SLC_r32_copy(src1_backup, 1, src1, 1, SLC_ARRAYSIZE(src1));
        SLC_r32_swap(src0, src1, swapbuffer, SLC_ARRAYSIZE(src0));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src0); i++)
        {
            if (!SLC_r32_areequal(src0[i], src1_backup[i], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r32_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
        if (err) break;
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src1); i++)
        {
            if (!SLC_r32_areequal(src1[i], src0_backup[i], SLC_r32_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r32_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_NumbersCopyUT_r32(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_r32_copyUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r32_set0UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r32_set1UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r32_swapUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion
#pragma region SLC_NumbersCopyUT_with_number_type_SLC_r64_t.
SLC_errno_t SLC_r64_copyUT(SLC_i32_t settings)
{
    SLC_r64_t src[] = { SLC_r64_rand, SLC_r64_rand, SLC_r64_rand, SLC_r64_rand };
    SLC_r64_t dst[SLC_ARRAYSIZE(src)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r64_copy(dst, 1, src, 1, SLC_ARRAYSIZE(src));
        if (SLC_ARRAYSIZE(src) != 4)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in SLC_ARRAYSIZE() @ %s,%d\n", __func__, __LINE__);
            break;
        }
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (src[i] != dst[i])
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r64_copy() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_set0UT(SLC_i32_t settings)
{
    SLC_r64_t src[] = { SLC_r64_rand, SLC_r64_rand, SLC_r64_rand, SLC_r64_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r64_set0(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_r64_areequal(src[i], SLC_r64_units[0], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r64_set0() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_set1UT(SLC_i32_t settings)
{
    SLC_r64_t src[] = { SLC_r64_rand, SLC_r64_rand, SLC_r64_rand, SLC_r64_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r64_set1(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_r64_areequal(src[i], SLC_r64_units[1], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r64_set1() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_swapUT(SLC_i32_t settings)
{
    SLC_r64_t src0[] = { SLC_r64_rand, SLC_r64_rand, SLC_r64_rand, SLC_r64_rand };
    SLC_r64_t src1[] = { SLC_r64_rand, SLC_r64_rand, SLC_r64_rand, SLC_r64_rand };
    SLC_r64_t src0_backup[SLC_ARRAYSIZE(src0)], src1_backup[SLC_ARRAYSIZE(src1)];
    SLC_r64_t swapbuffer[SLC_ARRAYSIZE(src0)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_r64_copy(src0_backup, 1, src0, 1, SLC_ARRAYSIZE(src0));
        SLC_r64_copy(src1_backup, 1, src1, 1, SLC_ARRAYSIZE(src1));
        SLC_r64_swap(src0, src1, swapbuffer, SLC_ARRAYSIZE(src0));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src0); i++)
        {
            if (!SLC_r64_areequal(src0[i], src1_backup[i], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r64_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
        if (err) break;
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src1); i++)
        {
            if (!SLC_r64_areequal(src1[i], src0_backup[i], SLC_r64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_r64_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_NumbersCopyUT_r64(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_r64_copyUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r64_set0UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r64_set1UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_r64_swapUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion
#pragma region SLC_NumbersCopyUT_with_number_type_SLC_c64_t.
SLC_errno_t SLC_c64_copyUT(SLC_i32_t settings)
{
    SLC_c64_t src[] = { SLC_c64_rand, SLC_c64_rand, SLC_c64_rand, SLC_c64_rand };
    SLC_c64_t dst[SLC_ARRAYSIZE(src)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c64_copy(dst, 1, src, 1, SLC_ARRAYSIZE(src));
        if (SLC_ARRAYSIZE(src) != 4)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in SLC_ARRAYSIZE() @ %s,%d\n", __func__, __LINE__);
            break;
        }
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (src[i] != dst[i])
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c64_copy() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_set0UT(SLC_i32_t settings)
{
    SLC_c64_t src[] = { SLC_c64_rand, SLC_c64_rand, SLC_c64_rand, SLC_c64_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c64_set0(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_c64_areequal(src[i], SLC_c64_units[0], SLC_c64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c64_set0() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_set1UT(SLC_i32_t settings)
{
    SLC_c64_t src[] = { SLC_c64_rand, SLC_c64_rand, SLC_c64_rand, SLC_c64_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c64_set1(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_c64_areequal(src[i], SLC_c64_units[1], SLC_c64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c64_set1() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_swapUT(SLC_i32_t settings)
{
    SLC_c64_t src0[] = { SLC_c64_rand, SLC_c64_rand, SLC_c64_rand, SLC_c64_rand };
    SLC_c64_t src1[] = { SLC_c64_rand, SLC_c64_rand, SLC_c64_rand, SLC_c64_rand };
    SLC_c64_t src0_backup[SLC_ARRAYSIZE(src0)], src1_backup[SLC_ARRAYSIZE(src1)];
    SLC_c64_t swapbuffer[SLC_ARRAYSIZE(src0)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c64_copy(src0_backup, 1, src0, 1, SLC_ARRAYSIZE(src0));
        SLC_c64_copy(src1_backup, 1, src1, 1, SLC_ARRAYSIZE(src1));
        SLC_c64_swap(src0, src1, swapbuffer, SLC_ARRAYSIZE(src0));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src0); i++)
        {
            if (!SLC_c64_areequal(src0[i], src1_backup[i], SLC_c64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c64_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
        if (err) break;
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src1); i++)
        {
            if (!SLC_c64_areequal(src1[i], src0_backup[i], SLC_c64_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c64_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_NumbersCopyUT_c64(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_c64_copyUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_c64_set0UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_c64_set1UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_c64_swapUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion
#pragma region SLC_NumbersCopyUT_with_number_type_SLC_c128_t.
SLC_errno_t SLC_c128_copyUT(SLC_i32_t settings)
{
    SLC_c128_t src[] = { SLC_c128_rand, SLC_c128_rand, SLC_c128_rand, SLC_c128_rand };
    SLC_c128_t dst[SLC_ARRAYSIZE(src)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c128_copy(dst, 1, src, 1, SLC_ARRAYSIZE(src));
        if (SLC_ARRAYSIZE(src) != 4)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in SLC_ARRAYSIZE() @ %s,%d\n", __func__, __LINE__);
            break;
        }
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (src[i] != dst[i])
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c128_copy() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_set0UT(SLC_i32_t settings)
{
    SLC_c128_t src[] = { SLC_c128_rand, SLC_c128_rand, SLC_c128_rand, SLC_c128_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c128_set0(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_c128_areequal(src[i], SLC_c128_units[0], SLC_c128_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c128_set0() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_set1UT(SLC_i32_t settings)
{
    SLC_c128_t src[] = { SLC_c128_rand, SLC_c128_rand, SLC_c128_rand, SLC_c128_rand };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c128_set1(src, 1, SLC_ARRAYSIZE(src));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src); i++)
        {
            if (!SLC_c128_areequal(src[i], SLC_c128_units[1], SLC_c128_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c128_set1() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_swapUT(SLC_i32_t settings)
{
    SLC_c128_t src0[] = { SLC_c128_rand, SLC_c128_rand, SLC_c128_rand, SLC_c128_rand };
    SLC_c128_t src1[] = { SLC_c128_rand, SLC_c128_rand, SLC_c128_rand, SLC_c128_rand };
    SLC_c128_t src0_backup[SLC_ARRAYSIZE(src0)], src1_backup[SLC_ARRAYSIZE(src1)];
    SLC_c128_t swapbuffer[SLC_ARRAYSIZE(src0)];
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_c128_copy(src0_backup, 1, src0, 1, SLC_ARRAYSIZE(src0));
        SLC_c128_copy(src1_backup, 1, src1, 1, SLC_ARRAYSIZE(src1));
        SLC_c128_swap(src0, src1, swapbuffer, SLC_ARRAYSIZE(src0));
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src0); i++)
        {
            if (!SLC_c128_areequal(src0[i], src1_backup[i], SLC_c128_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c128_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
        if (err) break;
        for (SLC_size_t i = 0; i < SLC_ARRAYSIZE(src1); i++)
        {
            if (!SLC_c128_areequal(src1[i], src0_backup[i], SLC_c128_stdtol))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Fail in SLC_c128_swap() @ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_NumbersCopyUT_c128(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_c128_copyUT, 0, __func__, __LINE__);
        SLC_test(err, SLC_c128_set0UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_c128_set1UT, 0, __func__, __LINE__);
        SLC_test(err, SLC_c128_swapUT, 0, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion

SLC_errno_t SLC_NumbersCopyUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_r32_copyUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r32_set0UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r32_set1UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r32_swapUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r64_copyUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r64_set0UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r64_set1UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_r64_swapUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c64_copyUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c64_set0UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c64_set1UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c64_swapUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c128_copyUT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c128_set0UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c128_set1UT, settings, __func__, __LINE__);
        SLC_test(err, SLC_c128_swapUT, settings, __func__, __LINE__);
    } while (0);
    return err;
}
