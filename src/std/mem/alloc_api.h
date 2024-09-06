#ifndef ALLOC_API_H
#define ALLOC_API_H
#include "../../decl/decl.h"

struct BD_t;

typedef struct BD_t {
    int blksz;
    struct BD_t* prev;
    struct BD_t* next;
} BD_t;

typedef struct HEAP_INFO_t {
    void* heap;
    size_t sz;
    BD_t* alloc_dll;
    BD_t* avail_dll;

    BD_t dummy1;
    BD_t dummy2;
} HEAP_INFO_t;

void* alloc(HEAP_INFO_t* heapinfo, size_t sz);
void initalloc(HEAP_INFO_t* heapinfo);
void memfree(HEAP_INFO_t* heapinfo, void* ptr);

#endif
