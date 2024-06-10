#include "../include/common.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define INPUT 4096

static char* gethome();
char* ConcatenateCWD(char Cwd[MAXBUF]);

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

