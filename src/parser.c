#include "include/asc_macros.h"
#include "include/common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUF 8192

void Parser(char Str[MAXBUF])
{
    unsigned long Siz = strlen(Str);

    if (Siz > MAXBUF)
    {
        printf("buffer overflow\n");
        exit(1);
    }

    if (!strcmp(Str, "help"))
    {
        printf("clrscr: clear screen\n");
        printf("goto: change directory\n");
        printf("exit: close the shell\n");
        printf("dir: list directories\n");
        printf("mkf: make file");
        printf("mkd: make directory\n");
        printf("rmf: delete file\n");
        printf("rmd: delete directory\n");
        printf("..: step back a directory\n");
    }

    if (!strcmp(Str, "out $OS"))
    {
        char* System = PrintOS();
        printf("%s\n", System);

        free(System);
    }

    if (!strncmp(Str, "clrscr", 6))
        ClearScreen(Str);

    if (!strcmp(Str, "exit"))
        exit(0);

    if (!strcmp(Str, "dir"))
        Ls();

    if (!strcmp(Str, ".."))
        chdir("..");

    if (!strncmp(Str, "goto", 4))
        DirSwitcher(Str);

    if (
        !strncmp(Str, "mkf", 3) ||
        !strncmp(Str, "mkd", 3) ||
        !strncmp(Str, "rmd", 3) ||
        !strncmp(Str, "rmf", 3)
    )
        PrepareForCreation(Str);
}

