#include "std/symbols.h"
#include "decl/decl.h"
#include "std/mem.h"
#include "std/num.h"
#include "std/str.h"
#include "std/io.h"

int main(int argc, char** argv)
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
