#define MAIN
#include "../shared/incl.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void getsh(FILE* fp, char file[])
{
    char* ln = (char*)malloc(sizeof(char) * 1024);
    if (ln == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int _sz = getindentsz(file);
    int ln_count = 0;
    int via = 0;

    while (fgets(ln, 1024, fp) != NULL)
    {
        ln[strcspn(ln, "\n")] = '\0';

        if (strstr(ln, VIA) != NULL)
        {
            via = 1;

            if (strcmp(ln + strlen(VIA), ATH) == 0)
            {
                rewind(fp);
                interpreter(fp, _sz);
            }

            else
            {
                printf("Other shells are not supported at this point\n");
                free(ln);
                return;
            }
        }

        ln_count++;
    }

    if (!via)
        printf("Missing `via` directive\n");

    free(ln);
}
