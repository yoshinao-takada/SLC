#include "SLC/SLC_DLink.h"
#include <stdlib.h>
#include <alloca.h>

SLC_PDLink_t SLC_DLink_Alloca(SLC_size_t n, SLC_size_t additional_bytes)
{
    SLC_size_t allocsize = (additional_bytes + sizeof(SLC_DLink_t)) * n;
    return (SLC_PDLink_t)alloca(allocsize);
}

SLC_PDLink_t SLC_DLink_Alloc(SLC_size_t n, SLC_size_t additional_bytes)
{
    SLC_size_t allocsize = (additional_bytes + sizeof(SLC_DLink_t)) * n;
    return (SLC_PDLink_t)malloc(allocsize);
}

void SLC_DLink_AddPrev(SLC_PDLink_t at, SLC_PDLink_t new_node)
{
    SLC_PDLink_t prev_node = at->prev;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    at->prev = new_node;
}

void SLC_DLink_AddNextr(SLC_PDLink_t at, SLC_PDLink_t new_node)
{
    SLC_PDLink_t next_node = at->next;
    next_node->prev = new_node;
    new_node->next = next_node;
    at->next = new_node;
}

SLC_size_t SLC_DLink_Count(SLC_PDLink_t at)
{
    SLC_size_t count = 0;
    SLC_PDLink_t node = at->next;
    while (node != at)
    {
        count++;
        node = node->next;
    }
    return count;
}

SLC_PDLink_t SLC_DLink_Peek(SLC_PDLink_t anchor, SLC_i32_t offset)
{
    SLC_PDLink_t target = anchor;
    do {
        target = target->next;
    } while (--offset);
    return target;
}

SLC_PDLink_t SLC_DLink_Remove(SLC_PDLink_t anchor, SLC_i32_t offset)
{
    SLC_PDLink_t target = anchor;
    do {
        target = target->next;
    } while (--offset);
    return SLC_DLink_RemoveThis(anchor, target);
}

SLC_PDLink_t SLC_DLink_RemoveThis(SLC_PDLink_t anchor, SLC_PDLink_t toRemove)
{
    if (toRemove == anchor)
    {
        return NULL;
    }
    toRemove->next->prev = toRemove->prev;
    toRemove->prev->next = toRemove->next;
    toRemove->prev = toRemove->next = toRemove;
    return toRemove;
}
