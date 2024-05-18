#include "../include/common.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXBUF 8192
#define INPUT 4096

static char* gethome();
char* ConcatenateCWD(char Cwd[MAXBUF]);
void Parser(char Str[MAXBUF]);

const char Start[] = "~";

int Shell(int argc, char** argv)
{
    char* Home = gethome();
    char* CCwd;

    char Cwd[MAXBUF];
    char Ui[INPUT];

    while (1)
    {
        Home = gethome();
        getcwd(Cwd, sizeof(Cwd));

        getcwd(Cwd, MAXBUF);
        unsigned long Len = strlen(Home);

        char* Path = Cwd + Len;
        unsigned long PathSize = strlen(Path);

        memmove(Path + strlen(Start), Path, PathSize + 1);
        strncpy(Path, Start, strlen(Start)); 

        printf("%s\n", Path);
        printf("> ");

        fgets(Ui, INPUT, stdin);
        Ui[strcspn(Ui, "\n")] = 0;

        Parser(Ui);
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
        printf("dir: list directories\n");
        printf("goto: change directory\n");
        printf("exit: close the shell\n");
    }

    if (!strcmp(Str, "exit"))
        exit(0);

    if (!strcmp(Str, "dir"))
        Ls();

    if (!strcmp(Str, ".."))
        chdir("..");

    if (!strncmp(Str, "goto", 4))
        DirSwitcher(Str);
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

