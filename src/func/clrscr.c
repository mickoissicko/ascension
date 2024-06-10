#include <string.h>
#include <stdio.h>

#define UNINITIALISED -1
#define MAX_VAL 247896
#define MAX_LEN 8

void ClearScreen(char Str[])
{
    char Discard[MAX_LEN];
    int Mode = UNINITIALISED;

    sscanf(Str, "%s %d", Discard, &Mode);

    if (Mode == UNINITIALISED || Mode == 0)
        printf("\e[1;1H\e[2J");

    else if (Mode != UNINITIALISED && Mode == 1)
    {
        int Count = 0;

        while (Count <= MAX_VAL)
        {
            printf("\n");
            Count++;
        }
    }
}

