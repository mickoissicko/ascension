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

        if (!strcmp(Path, "~"))
            chdir(gethome());

        if (Path != NULL && !!strcmp(Path, "~"))
        {
            if (chdir(Path) != 0)
                perror("Could not go to specified path\n");
        }
}

