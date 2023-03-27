#include "SLC/SLC_NumbersCopy.h"
#include "SLC/SLC_MiniBLAS.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <assert.h>
#include <alloca.h>
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r32_t
typedef struct {
    // source vectors[0], [1]
    SLC_r32_t src0[4];
    SLC_r32_t src1[4];
    // scales
    SLC_r32_t scales[4];
    // sum of source vectors
    SLC_r32_t src0_plus_src1[4];
    // scaled sum of source vectors, scaling factor is scales[0]
    SLC_r32_t src0_plus_scales0_x_src1[4];
    // src0 scaled by scales[0]
    SLC_r32_t scaled_src0[4];
    // e-by-e product
    SLC_r32_t src0_x_src1_ebe[4];
    // innerproduct, sum, abssum, tolerance
    SLC_r32_t innerproduct;
    SLC_r32_t sum_src0;
    SLC_r32_t abssum_src0;
    SLC_r32_t tolerance;
} MiniBLASUT_r32_params_t;

SLC_errno_t SLC_r32_copyconjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* conjugated = alloca(allocsize);
        SLC_r32_copyconj(conjugated, 1, params->src0, 1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(SLC_r32_conj(params->src0[i]), conjugated[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_addipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* sum = alloca(allocsize);
        SLC_r32_copy(sum,1, params->src0, 1, count);
        SLC_r32_addip(sum, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_scaleipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* scaled = alloca(allocsize);
        SLC_r32_copy(scaled,1, params->src0, 1, count);
        SLC_r32_scaleip(scaled, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->scaled_src0[i], scaled[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_scaleaddipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* sum = alloca(allocsize);
        SLC_r32_copy(sum, 1, params->src0, 1, count);
        SLC_r32_scaleaddip(sum, params->src1, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->src0_plus_scales0_x_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_multiplyebeipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* products = alloca(allocsize);
        SLC_r32_copy(products, 1, params->src0, 1, count);
        SLC_r32_multiplyebeip(products, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_addsubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* sum = alloca(allocsize);
        SLC_r32_addsubs(sum, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_scalesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* products = alloca(allocsize);
        SLC_r32_scalesubs(products, params->src0, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->scaled_src0[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_multiplyebesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;    
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r32_t);
        SLC_r32_t* products = alloca(allocsize);
        SLC_r32_multyplyebesubs(products, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r32_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_innerproductUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_r32_t innerproduct = 
            SLC_r32_innerproduct(params->src0, params->src1, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r32_areequal(params->innerproduct, innerproduct, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_sumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_r32_t sum = SLC_r32_sum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r32_areequal(params->sum_src0, sum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_abssumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r32_params_t* params = (const MiniBLASUT_r32_params_t*)(args->data);
        SLC_r32_t abssum = SLC_r32_abssum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r32_areequal(params->abssum_src0, abssum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r32_MiniBLASUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r32_copyconjUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_addipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_scaleipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_scaleaddipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_multiplyebeipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_addsubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_scalesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_multiplyebesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_innerproductUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_sumUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r32_abssumUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r32_t
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r64_t
typedef struct {
    // source vectors[0], [1]
    SLC_r64_t src0[4];
    SLC_r64_t src1[4];
    // scales
    SLC_r64_t scales[4];
    // sum of source vectors
    SLC_r64_t src0_plus_src1[4];
    // scaled sum of source vectors, scaling factor is scales[0]
    SLC_r64_t src0_plus_scales0_x_src1[4];
    // src0 scaled by scales[0]
    SLC_r64_t scaled_src0[4];
    // e-by-e product
    SLC_r64_t src0_x_src1_ebe[4];
    // innerproduct, sum, abssum, tolerance
    SLC_r64_t innerproduct;
    SLC_r64_t sum_src0;
    SLC_r64_t abssum_src0;
    SLC_r64_t tolerance;
} MiniBLASUT_r64_params_t;

SLC_errno_t SLC_r64_copyconjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* conjugated = alloca(allocsize);
        SLC_r64_copyconj(conjugated, 1, params->src0, 1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(SLC_r64_conj(params->src0[i]), conjugated[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_addipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* sum = alloca(allocsize);
        SLC_r64_copy(sum,1, params->src0, 1, count);
        SLC_r64_addip(sum, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_scaleipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* scaled = alloca(allocsize);
        SLC_r64_copy(scaled,1, params->src0, 1, count);
        SLC_r64_scaleip(scaled, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->scaled_src0[i], scaled[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_scaleaddipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* sum = alloca(allocsize);
        SLC_r64_copy(sum, 1, params->src0, 1, count);
        SLC_r64_scaleaddip(sum, params->src1, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->src0_plus_scales0_x_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_multiplyebeipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* products = alloca(allocsize);
        SLC_r64_copy(products, 1, params->src0, 1, count);
        SLC_r64_multiplyebeip(products, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_addsubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* sum = alloca(allocsize);
        SLC_r64_addsubs(sum, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_scalesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* products = alloca(allocsize);
        SLC_r64_scalesubs(products, params->src0, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->scaled_src0[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_multiplyebesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;    
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_r64_t);
        SLC_r64_t* products = alloca(allocsize);
        SLC_r64_multyplyebesubs(products, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_r64_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_innerproductUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_r64_t innerproduct = 
            SLC_r64_innerproduct(params->src0, params->src1, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r64_areequal(params->innerproduct, innerproduct, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_sumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_r64_t sum = SLC_r64_sum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r64_areequal(params->sum_src0, sum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_abssumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_r64_params_t* params = (const MiniBLASUT_r64_params_t*)(args->data);
        SLC_r64_t abssum = SLC_r64_abssum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r64_areequal(params->abssum_src0, abssum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_r64_MiniBLASUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r64_copyconjUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_addipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_scaleipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_scaleaddipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_multiplyebeipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_addsubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_scalesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_multiplyebesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_innerproductUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_sumUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_abssumUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_r64_t
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c64_t
typedef struct {
    // source vectors[0], [1]
    SLC_c64_t src0[4];
    SLC_c64_t src1[4];
    // scales
    SLC_c64_t scales[4];
    // sum of source vectors
    SLC_c64_t src0_plus_src1[4];
    // scaled sum of source vectors, scaling factor is scales[0]
    SLC_c64_t src0_plus_scales0_x_src1[4];
    // src0 scaled by scales[0]
    SLC_c64_t scaled_src0[4];
    // e-by-e product
    SLC_c64_t src0_x_src1_ebe[4];
    // innerproduct, sum, abssum, tolerance
    SLC_c64_t innerproduct;
    SLC_c64_t sum_src0;
    SLC_r32_t abssum_src0;
    SLC_r32_t tolerance;
} MiniBLASUT_c64_params_t;

SLC_errno_t SLC_c64_copyconjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* conjugated = alloca(allocsize);
        SLC_c64_copyconj(conjugated, 1, params->src0, 1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(SLC_c64_conj(params->src0[i]), conjugated[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_addipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* sum = alloca(allocsize);
        SLC_c64_copy(sum,1, params->src0, 1, count);
        SLC_c64_addip(sum, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_scaleipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* scaled = alloca(allocsize);
        SLC_c64_copy(scaled,1, params->src0, 1, count);
        SLC_c64_scaleip(scaled, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->scaled_src0[i], scaled[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_scaleaddipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* sum = alloca(allocsize);
        SLC_c64_copy(sum, 1, params->src0, 1, count);
        SLC_c64_scaleaddip(sum, params->src1, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->src0_plus_scales0_x_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_multiplyebeipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* products = alloca(allocsize);
        SLC_c64_copy(products, 1, params->src0, 1, count);
        SLC_c64_multiplyebeip(products, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_addsubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* sum = alloca(allocsize);
        SLC_c64_addsubs(sum, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_scalesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* products = alloca(allocsize);
        SLC_c64_scalesubs(products, params->src0, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->scaled_src0[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_multiplyebesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;    
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c64_t);
        SLC_c64_t* products = alloca(allocsize);
        SLC_c64_multyplyebesubs(products, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c64_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_innerproductUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_c64_t innerproduct = 
            SLC_c64_innerproduct(params->src0, params->src1, SLC_ARRAYSIZE(params->src0));
        if (!SLC_c64_areequal(params->innerproduct, innerproduct, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_sumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_c64_t sum = SLC_c64_sum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_c64_areequal(params->sum_src0, sum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_abssumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c64_params_t* params = (const MiniBLASUT_c64_params_t*)(args->data);
        SLC_r32_t abssum = SLC_c64_abssum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r32_areequal(params->abssum_src0, abssum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c64_MiniBLASUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_c64_copyconjUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_addipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_scaleipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_scaleaddipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_multiplyebeipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_addsubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_scalesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_multiplyebesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_innerproductUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_sumUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_abssumUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c64_t
#pragma region Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c128_t
typedef struct {
    // source vectors[0], [1]
    SLC_c128_t src0[4];
    SLC_c128_t src1[4];
    // scales
    SLC_c128_t scales[4];
    // sum of source vectors
    SLC_c128_t src0_plus_src1[4];
    // scaled sum of source vectors, scaling factor is scales[0]
    SLC_c128_t src0_plus_scales0_x_src1[4];
    // src0 scaled by scales[0]
    SLC_c128_t scaled_src0[4];
    // e-by-e product
    SLC_c128_t src0_x_src1_ebe[4];
    // innerproduct, sum, abssum, tolerance
    SLC_c128_t innerproduct;
    SLC_c128_t sum_src0;
    SLC_r64_t abssum_src0;
    SLC_r64_t tolerance;
} MiniBLASUT_c128_params_t;

SLC_errno_t SLC_c128_copyconjUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* conjugated = alloca(allocsize);
        SLC_c128_copyconj(conjugated, 1, params->src0, 1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(SLC_c128_conj(params->src0[i]), conjugated[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_addipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* sum = alloca(allocsize);
        SLC_c128_copy(sum,1, params->src0, 1, count);
        SLC_c128_addip(sum, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_scaleipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* scaled = alloca(allocsize);
        SLC_c128_copy(scaled,1, params->src0, 1, count);
        SLC_c128_scaleip(scaled, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->scaled_src0[i], scaled[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_scaleaddipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* sum = alloca(allocsize);
        SLC_c128_copy(sum, 1, params->src0, 1, count);
        SLC_c128_scaleaddip(sum, params->src1, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->src0_plus_scales0_x_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_multiplyebeipUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* products = alloca(allocsize);
        SLC_c128_copy(products, 1, params->src0, 1, count);
        SLC_c128_multiplyebeip(products, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_addsubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* sum = alloca(allocsize);
        SLC_c128_addsubs(sum, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->src0_plus_src1[i], sum[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_scalesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* products = alloca(allocsize);
        SLC_c128_scalesubs(products, params->src0, &params->scales[0], count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->scaled_src0[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_multiplyebesubsUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;    
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_size_t count = SLC_ARRAYSIZE(params->src0);
        SLC_size_t allocsize = count * sizeof(SLC_c128_t);
        SLC_c128_t* products = alloca(allocsize);
        SLC_c128_multyplyebesubs(products, params->src0, params->src1, count);
        for (SLC_size_t i = 0; i < count; i++)
        {
            if (!SLC_c128_areequal(params->src0_x_src1_ebe[i], products[i], params->tolerance))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_innerproductUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_c128_t innerproduct = 
            SLC_c128_innerproduct(params->src0, params->src1, SLC_ARRAYSIZE(params->src0));
        if (!SLC_c128_areequal(params->innerproduct, innerproduct, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_sumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_c128_t sum = SLC_c128_sum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_c128_areequal(params->sum_src0, sum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_abssumUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        const MiniBLASUT_c128_params_t* params = (const MiniBLASUT_c128_params_t*)(args->data);
        SLC_r64_t abssum = SLC_c128_abssum(params->src0, SLC_ARRAYSIZE(params->src0));
        if (!SLC_r64_areequal(params->abssum_src0, abssum, params->tolerance))
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "@ %s,%d\n", __func__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_c128_MiniBLASUT(SLC_PCTestArgs_t args)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_c128_copyconjUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_addipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_scaleipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_scaleaddipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_multiplyebeipUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_addsubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_scalesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_multiplyebesubsUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_innerproductUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_sumUT, args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_abssumUT, args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
#pragma endregion Unit_tests_for_MiniBLAS_with_base_number_type_SLC_c128_t
#pragma region r32_test_data
MiniBLASUT_r32_params_t r32_params = {
    { -1.0f, 2.0f, -2.1f, 3.3f },
    { 2.0f, -2.1f, 3.3f, -1.5f },
    { 1.1f, -1.1f, -0.9f, 0.85f },
    { 1.0f, -0.1f, 1.2f, 1.8f },
    { 1.2f, -0.31f, 1.53f, 1.65f },
    { -1.1f, 2.2f, -2.31f, 3.63f },
    { -2.0f, -4.2f, -6.93f, -4.95f },
    -18.08f, 2.2f, 8.4f, SLC_r32_stdtol
};
#pragma endregion
#pragma region r64_test_data
MiniBLASUT_r64_params_t r64_params = {
    { -1.0, 2.0, -2.1, 3.3 },
    { 2.0, -2.1, 3.3, -1.5 },
    { 1.1, -1.1, -0.9, 0.85 },
    { 1.0, -0.1, 1.2, 1.8 },
    { 1.2, -0.31, 1.53, 1.65 },
    { -1.1, 2.2, -2.31, 3.63 },
    { -2.0, -4.2, -6.93, -4.95 },
    -18.08, 2.2, 8.4, SLC_r64_stdtol
};
#pragma endregion
#pragma region c64_test_data
MiniBLASUT_c64_params_t c64_params = {
    { CMPLXF(-1.0f, 2.0f), CMPLXF(2.0f, -2.1f), CMPLXF(-2.1f, 3.3f), CMPLXF(3.3f, -1.0f) },
    { CMPLXF(2.0f, -2.1f), CMPLXF(-2.1f, 3.3f), CMPLXF(3.3f, -1.5f), CMPLXF(-1.5f, 2.0f) },
    { CMPLXF(1.1f, -1.1f), CMPLXF(-1.1f, -0.9f), CMPLXF(-0.9f, 0.85f), CMPLXF(0.85f, 1.1f) },
    { CMPLXF(1.0f,-0.1f), CMPLXF(-0.1f,1.2f), CMPLXF(1.2f,1.8f), CMPLXF(1.8f,1.0f) },
    { CMPLXF(-1.11f,-2.51f), CMPLXF(3.32f,3.84f), CMPLXF(-0.12f,-1.98f), CMPLXF(3.85f,2.85f) },
    { CMPLXF(1.1f, 3.3f), CMPLXF(-0.11f,-4.51f), CMPLXF(1.32f, 5.94f), CMPLXF(2.53f,-4.73f) },
    { CMPLXF(2.2f,6.1f), CMPLXF(2.73f,11.01f), CMPLXF(-1.98f,14.04f), CMPLXF(-2.95f,8.1f) },
    CMPLXF(-36.16f,2.35f), CMPLXF(2.2f, 2.2f), 12.496f, SLC_c64_stdtol
 };
#pragma endregion
#pragma region c128_test_data
MiniBLASUT_c128_params_t c128_params = {
    { CMPLX(-1.0, 2.0), CMPLX(2.0, -2.1), CMPLX(-2.1, 3.3), CMPLX(3.3, -1.0) },
    { CMPLX(2.0, -2.1), CMPLX(-2.1, 3.3), CMPLX(3.3, -1.5), CMPLX(-1.5, 2.0) },
    { CMPLX(1.1, -1.1), CMPLX(-1.1, -0.9), CMPLX(-0.9, 0.85), CMPLX(0.85, 1.1) },
    { CMPLX(1.0,-0.1), CMPLX(-0.1,1.2), CMPLX(1.2,1.8), CMPLX(1.8,1.0) },
    { CMPLX(-1.11,-2.51), CMPLX(3.32,3.84), CMPLX(-0.12,-1.98), CMPLX(3.85,2.85) },
    { CMPLX(1.1,3.3), CMPLX(-0.11,-4.51), CMPLX(1.32, 5.94), CMPLX(2.53,-4.73) },
    { CMPLX(2.2,6.1), CMPLX(2.73,11.01), CMPLX(-1.98,14.04), CMPLX(-2.95,8.1) },
    CMPLX(-36.16,2.35), CMPLX(2.2, 2.2), 12.496, SLC_c64_stdtol
};
#pragma endregion

static const SLC_TestArgs_t r32_args = { 0, (void*)&r32_params };
static const SLC_TestArgs_t r64_args = { 0, (void*)&r64_params };
static const SLC_TestArgs_t c64_args = { 0, (void*)&c64_params };
static const SLC_TestArgs_t c128_args = { 0, (void*)&c128_params };

SLC_errno_t SLC_MiniBLASUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test2(err, SLC_r32_MiniBLASUT, &r32_args, __func__, __LINE__);
        SLC_test2(err, SLC_r64_MiniBLASUT, &r64_args, __func__, __LINE__);
        SLC_test2(err, SLC_c64_MiniBLASUT, &c64_args, __func__, __LINE__);
        SLC_test2(err, SLC_c128_MiniBLASUT, &c128_args, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}
