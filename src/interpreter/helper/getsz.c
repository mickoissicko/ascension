#define VAR
#include "../../shared/incl.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getindentsz(char f[])
{
    char ln[8192];

    int ln_exists = 0;
    int i = 0;
    int _i;

    FILE* fp = fopen(f, "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    while (fgets(ln, sizeof(ln), fp) != NULL && i < 2)
    {
        if (strncmp(ln, var(6), strlen(var(6))) == 0)
        {
            for (_i = 0; ln[_i] != '\0'; _i++)
                if (ln[_i] == '=')
                {
                    if (ln[_i + 1] == ' ')
                        _i += 2;

                    else
                        _i += 1;
                }

            ln_exists = 1;
        }

        else ln_exists = 0;

        i++;
    }

    ln[strcspn(ln, "\n")] = '\0';

    fclose(fp);

    if (!ln_exists) return DEFAULT_INDENT_SZ;
    else return atoi((ln + _i) - 2);
}
