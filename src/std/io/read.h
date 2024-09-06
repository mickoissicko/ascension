#ifndef READ_H
#define READ_H
#include "../../decl/decl.h"
#include "../str/trm.h"

char* readinpt(void) {
    extern long read(int, char *, unsigned long);

    static char buf[8192];
    ssize_t readbytes;

    readbytes = read(0, buf, sizeof(buf) - 1);

    if (readbytes > 0)
        buf[readbytes] = '\0';
    else
        buf[0] = '\0';

    trmchr(buf, '\n');
    return buf;
}

#endif
