#ifndef DECL_H
#define DECL_H
#define NO_EXIT_EVENT "OK"
#define NORMAL_EXIT 500

typedef unsigned long size_t;
typedef long ssize_t;

static inline char* var(int var);
int proc(char inpt[]);
void stdshell(void);

inline void putchar(char c)
{
    extern long _write(int, const char *, unsigned long);
    (void) _write(1, &c, 1);
}

inline char getchar()
{
    extern long __read(int, char *, unsigned long);
    char c;
    (void) __read(0, &c, 1);
    return c;
}

#endif
