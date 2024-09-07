#ifndef MAP_H
#define MAP_H
#include "typedef.h"
#include "sym.h"

static inline char* var(int var)
{
    if (var == -1) RET PROMPT;
    if (var == 0) RET EXIT;
    if (var == 1) RET ECHO;
    if (var == 2) RET DEF;
}

#endif
