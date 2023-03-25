#if !defined(_SLC_DLINK_H)
#define _SLC_DLINK_H
#include "SLC/SLC_Numbers.h"
typedef struct SLC_DLink {
    struct SLC_DLink* prev;
    struct SLC_DLink* next;
} SLC_DLink_t, *SLC_PDLink_t;

// allocate new nodes
SLC_PDLink_t SLC_DLink_InitArray(void* node_array, SLC_size_t n, SLC_size_t additional_bytes);

#define SLC_DLink_Alloca(__n, __additional_bytes) SLC_DLink_InitArray( \
    alloca(__n * (sizeof(SLC_DLink_t) + __additional_bytes)), __n, __additional_bytes)
    
SLC_PDLink_t SLC_DLink_Alloc(SLC_size_t n, SLC_size_t additional_bytes);

// add a new node on at->prev.
void SLC_DLink_AddPrev(SLC_PDLink_t at, SLC_PDLink_t new_node);

// add a new node on at->next.
void SLC_DLink_AddNext(SLC_PDLink_t at, SLC_PDLink_t new_node);

// count nodes excluding at.
SLC_size_t SLC_DLink_Count(SLC_PDLink_t at);

// peek a node apart from anchor by offset.
// offset = 1 means the next node. offset = -1 means the previous node.
SLC_PDLink_t SLC_DLink_Peek(SLC_PDLink_t anchor, SLC_i32_t offset);
// remove a node apart from anchor by offset.
SLC_PDLink_t SLC_DLink_Remove(SLC_PDLink_t anchor, SLC_i32_t offset);
SLC_PDLink_t SLC_DLink_RemoveThis(SLC_PDLink_t anchor, SLC_PDLink_t toRemove);
#endif