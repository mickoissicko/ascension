#ifndef NEWLINE_H
#define NEWLINE_H
#include "../../decl/decl.h"
#include "../str.h"

void println(int br)
{
    if (br)
        putchar('\n');
}

void writeln(const char ln[])
{
    size_t len = lenstr(ln);

    for (size_t i = 0; i < len; ++i)
        putchar(ln[i]);
}

void writebuf(const char* buf)
{
    extern long write(int, const char *, unsigned long);

    write(1, buf, lenstr(buf));
}

#endif
