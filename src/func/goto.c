#include "../include/common.h"

#include <unistd.h>

#define MAXBUF 8192

void DirSwitcher(char Dir[])
{
    char Cwd[MAXBUF];
    getcwd(Cwd, sizeof(Cwd));

    char* Home = gethome();

    
}

