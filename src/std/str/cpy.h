#ifndef CPY_H
#define CPY_H
#include "put.h"

typedef struct
{
    char e[32];
} Command;

static inline size_t cpybytes(char* dst, const char* src, size_t sz)
{
    size_t len = 0;

    if (sz > 0)
    {
        while (*src && --sz > 0)
        {
            *dst++ = *src++;
            len++;
        }

        *dst = '\0';
    }

    while (*src++) len++;
    return len;
}

static inline void cpystr(char* dst, const char src[])
{
    putstr(dst, src, sizeof(dst));
}

static inline void cpystruct(Command* cmd, const char str[])
{
    putstr(cmd->e, str, sizeof(cmd->e));   
}

#endif
