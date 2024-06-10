#include "../include/common.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXBUF 8192
#define INPUT 4096

static char* gethome();
char* ConcatenateCWD(char Cwd[MAXBUF]);
void Parser(char Str[MAXBUF]);

const char Start[] = "~";

int Shell(int argc, char** argv)
{
    char* Home = gethome();
    char Cwd[MAXBUF];
    char* Ui;

    while (1)
    {
        Home = gethome();
        getcwd(Cwd, sizeof(Cwd));

        if (strstr(Cwd, Home))
        {
            unsigned long Len = strlen(Home);
            char* Path = Cwd + Len;
            unsigned long PathSize = strlen(Path);

            memmove(Path + strlen(Start), Path, PathSize + 1);
            strncpy(Path, Start, strlen(Start)); 

            printf("%s\n", Path);
        }

        else
        {
            printf("%s\n", Cwd);
        }

        printf("> ");

        Ui = readline("");
        if (Ui == NULL)
        {
            printf("Error reading input\n");
            continue;
        }

        add_history(Ui);
        Parser(Ui);

        free(Ui);
    }

    return 0;
}

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

char* ConcatenateCWD(char Cwd[MAXBUF])
{
    char* CCwd;
    CCwd = (char*)malloc(MAXBUF * sizeof(char));

    char* Home = gethome();

    if (strstr(Cwd, Home) != NULL)
        strcpy(CCwd, "~");
    else
        strcpy(CCwd, Cwd);

    return CCwd;
}

