#include "sh/shell.h"
#include "std/mem.h"
#include "std/num.h"
#include "std/str.h"
#include "std/io.h"

char* var(int var) {
    if (var == -1) return "-> ";
    if (var == 0) return "exit";
}

int main(int argc, char** argv) {
    for (;;) {
        writebuf(var(-1));
        char* s = readinpt();

        if (cmpstr(s, var(0)) == 0)
            break;
        else if (findsub(s, var(0)) == s)
            return makeint((s = ((s + lenstr(var(0))) + 1)));

        exec(s);
    }

    return 0;
}
