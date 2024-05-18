#include "../include/common.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAXBUF 8192

void DirSwitcher(char Dir[])
{
    char* Path = strtok(Dir, " ");
    Path = strtok(NULL, " ");

    if (Path == NULL)
    {
        printf("Too few or too many arguments\n");
        return;
    }

    if (Path[0] == '~' && Path[1] != '\0')
    {
        memmove(Path + strlen(gethome()), Path + 1, strlen(Path));
        memcpy(Path, gethome(), strlen(gethome()));

        printf("%s\n", Path);
    }

    if (!strcmp(Path, "~"))
        chdir(gethome());

    if (Path != NULL && !!strcmp(Path, "~"))
    {
        if (chdir(Path) != 0)
            perror("(!) Error");
    }
}

