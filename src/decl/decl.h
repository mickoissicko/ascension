#ifndef DECL_H
#define DECL_H

typedef unsigned long size_t;
typedef long ssize_t;

inline void putchar(char c) {
    extern long write(int, const char *, unsigned long);
    (void) write(1, &c, 1);
}

inline char getchar() {
    extern long read(int, char *, unsigned long);
    char c;
    (void) read(0, &c, 1);
    return c;
}

#endif
