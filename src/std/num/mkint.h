#ifndef MKINT_H
#define MKINT_H

static inline int makeint(char* s)
{
    int sign = 1;
    int _int = 0;
    int i = 0;

    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }

    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
            return -1;

        _int = _int * 10 + (s[i] - '0');
        i++;
    }

    return _int * sign;
}

#endif
