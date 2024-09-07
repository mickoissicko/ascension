#ifndef PUT_H
#define PUT_H
#include "../../decl/decl.h"

void putstr(char dst[], const char src[], size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; ++i)
        dst[i] = src[i];
    
    for (;i < n; ++i)
        dst[i] = '\0';
}

#endif
