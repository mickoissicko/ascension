#ifndef SUB_H
#define SUB_H
#define NULL 0

static inline char* findsub(const char* s1, const char* s2)
{
    if (!*s2)
        return (char*)s1;

    for (; *s1; s1++)
    {
        const char *p1 = s1;
        const char *p2 = s2;

        while (*p1 && *p2 && *p1 == *p2)
        {
            p1++;
            p2++;
        }

        if (!*p2)
            return (char*)s1;
    }

    return NULL;
}

#endif
