#define NORMAL_EXIT 500
#define STD_WRITE
#define MAIN
#define IO
#include "shared/incl.h"
#include "std/symbols.h"
#include "std/str/sub.h"
#include "std/str/len.h"
#include "std/str/cmp.h"
#include "std/io.h"

int proc(char* s)
{
    if (cmpstr(s, var(0)) == 0)
        return 0;

    if (findsub(s, var(4)) != NULL)
        stdparse(s, LS);

    if (findsub(s, var(3)) != NULL)
        stdparse(s, CD);

    if (findsub(s, var(5)) != NULL)
        stdparse(s, OPN);

    if (findsub(s, var(6)) != NULL)
        stdparse(s, RUN);

    return NORMAL_EXIT;
}
