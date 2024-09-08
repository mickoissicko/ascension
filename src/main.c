#define STD_WRITE
#define IO

#include "shared/incl.h"
#include "std/symbols.h"
#include "decl/decl.h"
#include "std/mem.h"
#include "std/num.h"
#include "std/str.h"
#include "std/io.h"
#include <unistd.h>

int main(void)
{
    for (;;)
    {
        writebuf(var(-1));
        char* s = readinpt();
        int retval = proc(s);

        if (retval != NORMAL_EXIT)
            return retval;
    }

    return 0;
}
