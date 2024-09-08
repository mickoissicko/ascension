#ifndef NEWLINE_H
#define NEWLINE_H
#include "../str/len.h"
#ifdef NO_LIB_C
#include "../../decl/decl.h"

#define println(br) \
    if (br)         \
        putchar('\n');

static inline void writeln(const char ln[])
{
    size_t len = lenstr(ln);

    for (size_t i = 0; i < len; ++i)
        putchar(ln[i]);
}
#endif

#ifdef STD_WRITE
#define writebuf(buf)                                     \
    write(1, buf, lenstr(buf));
#endif
#endif
