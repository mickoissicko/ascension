#ifndef TRM_H
#define TRM_H

void trmstr(char* s, char* r) {
    //
}

void trmchr(char* s, char r) {
    int i = 0, j = 0;

    while (s[i] != '\0') {
        if (s[i] != r)
            s[j++] = s[i];

        i++;
    }

    s[j] = '\0';
}

#endif
