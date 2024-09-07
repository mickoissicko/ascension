#ifndef FLUSH_H
#define FLUSH_H
#include "../../decl/decl.h"
#include "write.h"

typedef struct
{
    char* buf;
    size_t sz;
    size_t pos;
} Stream;

void fwriteln(Stream* stream)
{
    if (stream->buf && stream->pos > 0)
    {
        for (size_t i = 0; i < stream->pos; ++i)
            putchar(stream->buf[i]);

        stream->pos = 0;
    }
}

#endif
