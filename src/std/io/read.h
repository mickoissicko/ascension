#ifndef READ_H
#define READ_H
#include "../str/trm.h"
#ifdef NO_LIB_C
#include "../../decl/decl.h"
extern long read(int, char *, unsigned long);
#else
#include <unistd.h>
#endif

static inline char* readinpt(void)
{
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
