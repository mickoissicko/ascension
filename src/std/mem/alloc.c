#include "../../decl/decl.h"
#define NULL 0

struct BD_t;

typedef struct BD_t
{
    int blksz;
    struct BD_t* prev;
    struct BD_t* next;
} BD_t;

typedef struct HEAP_INFO_t
{
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

void initalloc(HEAP_INFO_t* heapinfo)
{
    heapinfo->alloc_dll = &(heapinfo->dummy1);
    heapinfo->alloc_dll->next = NULL;
    heapinfo->alloc_dll->prev = NULL;
    heapinfo->avail_dll = &(heapinfo->dummy2);
    heapinfo->avail_dll->prev = NULL;
    heapinfo->avail_dll->next = heapinfo->heap;
    heapinfo->avail_dll->next->blksz = heapinfo->sz - sizeof(BD_t);
    heapinfo->avail_dll->next->next = NULL;
    heapinfo->avail_dll->next->prev = heapinfo->avail_dll;
}

void* alloc(HEAP_INFO_t* heapinfo, size_t sz)
{
    BD_t* c = heapinfo->avail_dll->next;

    while(c != NULL)
    {
        int remaining = c->blksz-sz;

        if (remaining > 0)
        {
            if ((unsigned int)remaining > sizeof(BD_t))
            {
                c->blksz = sz;
                
                BD_t* newblk = (void*)c + sizeof(BD_t) + sz;
                newblk->blksz = remaining - sizeof(BD_t);

                c->prev->next = newblk;
                newblk->next = c->next;
                newblk->prev = c->prev;

                if(c->next != NULL)
                    c->next->prev = newblk;

            }

            else
            {
                c->prev->next = c->next;

                if (c->next != NULL)
                    c->next->prev = c->prev;
            }

            c->next = heapinfo->alloc_dll->next;
            heapinfo->alloc_dll->next = c;

            if (c->next != NULL)
                c->next->prev = c;

            c->prev = heapinfo->alloc_dll;

            return (void*)c + sizeof(BD_t);
        }

        c = c->next;
    }

    return NULL;
}

void memfree(HEAP_INFO_t* heapinfo, void* ptr)
{
    BD_t* bd = ptr - (sizeof(BD_t));

    bd->prev->next = bd->next;

    if(bd->next!=NULL)
        bd->next->prev = bd->prev;

    BD_t* c = heapinfo->avail_dll;

    while(c->next != NULL)
    {
        if(c->next > bd)
            break;

        c = c->next;
    }

    bd->next = c->next;
    c->next = bd;

    bd->prev = c;

    if(bd->next != NULL)
        bd->next->prev = bd;

    if (((void*)bd + sizeof(BD_t) + bd->blksz) == (bd->next))
    {
        bd->blksz = bd->blksz + sizeof(BD_t) + bd->next->blksz;
        bd->next = bd->next->next;

        if(bd->next != NULL)
            bd->next->prev = bd;
    }   

    if(((void*)c + sizeof(BD_t) + c->blksz) == bd)
    {
        c->blksz = c->blksz + sizeof(BD_t) + bd->blksz;
        c->next = bd->next;

        if(c->next != NULL)
            c->next->prev = c;
    }
}