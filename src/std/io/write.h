#ifndef NEWLINE_H
#define NEWLINE_H
#include "../../decl/decl.h"
#include "../str.h"

#define println(br) \
    if (br)         \
        putchar('\n');

static inline void writeln(const char ln[])
{
    size_t len = lenstr(ln);

    for (size_t i = 0; i < len; ++i)
        putchar(ln[i]);
}

#define writebuf(buf)                                     \
    extern long write(int, const char *, unsigned long);  \
    write(1, buf, lenstr(buf));

#endif
