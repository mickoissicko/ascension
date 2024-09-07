#include "std/str/sub.h"
#include "decl/decl.h"
#include "sh/shell.h"

int proc(char inpt[])
{
    char* _retval = run(inpt);

    if (cmpstr(_retval, NO_EXIT_EVENT) != 0)
        return makeint((_retval + lenstr(var(0)) + 1));

    return NORMAL_EXIT;
}
