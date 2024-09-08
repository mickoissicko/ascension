#define MAIN // for stdio.h
#include "../shared/incl.h"

void _read(char filename[])
{
    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    getsh(fp, filename);
    fclose(fp);
}
