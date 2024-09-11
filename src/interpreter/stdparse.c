#define STD_WRITE
#define MAIN
#define IO

#include "../shared/incl.h"
#include "../std/symbols.h"
#include "../std/str/len.h"
#include "../std/str/sub.h"
#include "../std/str/cmp.h"
#include "../std/io.h"
#include <unistd.h>

void p(void)
{
    putchar('\n');
}

void stdparse(char str[], char label[])
{
    if (cmpstr(label, LS) == 0)
    {
        if (checklsarg(str) == 1) ls(str + lenstr(LS) + 1);
        if (checklsarg(str) == 0) ls(".");
        p();
    }

    else if (cmpstr(label, CD) == 0)
        cd(str + lenstr(var(3)));

    else if (cmpstr(label, OPN) == 0)
        exec(str + lenstr(OPN));

    else if (cmpstr(label, RUN) == 0)
        _read(str + lenstr(RUN));
}
