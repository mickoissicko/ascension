#include <unistd.h>
#include <stdio.h>

void cd(char path[])
{
    if (chdir(path) != 0)
    {
        perror("cd");
        return;
    }
}
