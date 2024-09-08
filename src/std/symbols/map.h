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
    if (var == 3) RET CD;
    if (var == 4) RET LS;
    if (var == 5) RET OPN;
    if (var == 6) RET RUN;
}

#endif
