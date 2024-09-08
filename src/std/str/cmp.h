#ifndef CMP_H
#define CMP_H

static inline int cmpstr(const char* a, const char* b)
{
    for (;;)
    {
        if (*a != *b)
            return 1;

        if (*a == '\0')
            return 0;

        ++a;
        ++b;
    }
}

#endif
