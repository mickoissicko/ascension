#ifndef CHR_H
#define CHR_H

char* chrstr(const char* s, int c) {
    while (*s != (char)c) {
        if (*s == '\0')
            return 0;

        s++;
    }

    return (char*)s;
}

#endif
