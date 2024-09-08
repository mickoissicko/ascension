#ifndef LEN_H
#define LEN_H
#ifdef NO_LIB_C
#include "../../decl/decl.h"
#else
#include <stddef.h>
#endif

static inline size_t lenstr(const char str[])
{
    const char* s = str;

    while (*s)
        ++s;

    return (size_t)(s - str);
}

#endif
