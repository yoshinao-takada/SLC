# Doubly Linked List
The doubly linked list is defined in `SLCS_DLink.c/.h`.  
It provides the basic functionarities of doubly linked list but without any payload.  
The data type is declared as shwon below.
```
// Most basic double link
typedef struct SLC_DLink {
    struct SLC_DLink* prev;
    struct SLC_DLink* next;
} SLC_DLink_t, *SLC_PDLink_t;

// basic double link + node count
typedef struct SLC_DLinkAnchor {
    SLC_DLink_t link;
    SLC_size_t count;
} SLC_DLinkAnchor_t, *SLC_PDLinkAnchor_t;
#define SLC_DLINKANCHOR_DECL(__name) SLC_DLinkAnchor_t __name = { { &__name, &__name }, 0 }
```

It implements following methods.  
```
// allocate new nodes
SLC_PDLink_t SLC_DLink_Alloca(SLC_size_t n, SLC_size_t additional_bytes);
SLC_PDLink_t SLC_DLink_Alloc(SLC_size_t n, SLC_size_t additional_bytes);

// add a new node on at->prev.
void SLC_DLink_AddPrev(SLC_PDLink_t at, SLC_PDLink_t new_node);

// add a new node on at->next.
void SLC_DLink_AddNextr(SLC_PDLink_t at, SLC_PDLink_t new_node);

// peek a node apart from anchor by offset.
// offset = 1 means the next node. offset = -1 means the previous node.
SLC_PDLink_t SLC_DLink_Peek(SLC_PDLink_t anchor, SLC_i32_t offset);
// remove a node apart from anchor by offset.
SLC_PDLink_t SLC_DLink_Remove(SLC_PDLink_t anchor, SLC_i32_t offset);

//--------------------------------------------------------------------
// anchor must point an instance of SLC_DLinkAnchor_t in functions below.
//--------------------------------------------------------------------
// peek with node count check
SLC_PDLink_t SLC_DLink_SafePeek(SLC_PDLink_t anchor, SLC_i32_t offset);
// remove with node count check
SLC_PDLink_t SLC_DLink_SafeRemove(SLC_PDLink_t anchor, SLC_i32_t offset);
```
