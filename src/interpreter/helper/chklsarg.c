#define VAR
#include "../../shared/incl.h"
#include <string.h>

int checklsarg(const char program[])
{
    if (strncmp(program, var(5), strlen(var(5))) == 0) return 1;
    else return 0;

    return -1;
}
