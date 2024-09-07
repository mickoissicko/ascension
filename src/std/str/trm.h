#ifndef TRM_H
#define TRM_H

// static inline void trmstr(char* s, char* r) {}

static inline void trmchr(char* s, char r)
{
    int i = 0, j = 0;

    while (s[i] != '\0')
    {
        if (s[i] != r)
            s[j++] = s[i];

        i++;
    }

    s[j] = '\0';
}

#endif
