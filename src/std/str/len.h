#ifndef LEN_H
#define LEN_H
#include "../../decl/decl.h"

static inline size_t lenstr(const char str[])
{
    const char* s = str;

    while (*s)
        ++s;

    return (size_t)(s - str);
}

#endif
