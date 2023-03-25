#include "SLC/SLC_DLink.h"
#include "SLC/SLC_errno.h"
#include "SLC/SLC_Log.h"
#include <errno.h>
#define NODE_COUNT  12
#define ADDITIONAL_BYTES    8

typedef union {
    SLC_4i16_t i16; // maybe most frequently used
    SLC_i64_t i64;
    SLC_2i32_t i32;
    SLC_8i8_t i8;
    SLC_u64_t u64;
    SLC_2u32_t u32;
    SLC_4u16_t u16;
    SLC_8u8_t u8;
} DLinkTestData_t, *pDLinkTestData_t;
#define Get_i32(__p) (pDLinkTestData_t)(__p + 1);

static SLC_PDLink_t nodes = NULL;

SLC_errno_t SLC_DLinkScenario(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_DLink_t anchor = { &anchor, &anchor };
    const __PTRDIFF_TYPE__ stepsize = sizeof(SLC_DLink_t) + ADDITIONAL_BYTES;
    SLC_size_t node_count = 0;
    do {
        SLC_PDLink_t current = nodes;
        // Check initial values
        for (SLC_size_t i = 0; i < NODE_COUNT; i++)
        {
            SLC_u8_t* current_u8 = (SLC_u8_t*)current;
            SLC_u8_t* next_u8 = (SLC_u8_t*)(current->next);
            __PTRDIFF_TYPE__ diff = next_u8 - current_u8;
            if ((diff != stepsize) && (current->next != nodes))
            {
                err = EXIT_FAILURE;
                SLC_LogERR(err, "Maybe failed in SLC_DLink\n");
                break;
            }
        }
        if (err) break;

        // Test AddPrev, AddNext, and Count
        current = SLC_DLink_Remove(nodes, 1);
        pDLinkTestData_t data = Get_i32(current);
        SLC_DLink_AddPrev(&anchor, current);
        node_count = SLC_DLink_Count(nodes);
        if ((NODE_COUNT - 2) != node_count)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in SLC_DLink_Count() = %ld @ %s,%d\n", node_count, __func__, __LINE__);
            break;
        }
        node_count = SLC_DLink_Count(&anchor);
        if (1 != node_count)
        {
            err = EXIT_FAILURE;
            SLC_LogERR(err, "Fail in SLC_DLink_Count() = %ld @ %s,%d\n", node_count, __func__, __LINE__);
            break;
        }

        // Test Remove

        // Test RemoveThis
    } while (0);
    return err;
}

SLC_errno_t SLC_DLinkOnStackframe(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    nodes = SLC_DLink_Alloca(NODE_COUNT, ADDITIONAL_BYTES);
    do {
        SLC_test(err, SLC_DLinkScenario, settings, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_DLinkOnHeap(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    nodes = SLC_DLink_Alloc(NODE_COUNT, ADDITIONAL_BYTES);
    do {
        SLC_test(err, SLC_DLinkScenario, settings, __func__, __LINE__);
    } while (0);
    free(nodes);
    SLC_testend(err, __func__, __LINE__);
    return err;
}

SLC_errno_t SLC_DLinkUT(SLC_i32_t settings)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        SLC_test(err, SLC_DLinkOnHeap, settings, __func__, __LINE__);
        SLC_test(err, SLC_DLinkOnStackframe, settings, __func__, __LINE__);
    } while (0);
    SLC_testend(err, __func__, __LINE__);
    return err;
}