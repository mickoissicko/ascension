#define STD_WRITE
#define IO
#include "../../std/io.h"
#include <unistd.h>
#include <stdio.h>
#ifndef _WIN32
#include <sys/stat.h>
#include <dirent.h>

void ls(const char path[])
{
    DIR* dir = opendir(path);

    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    struct dirent* dent;
    struct stat sb;

    char fpath[8192];

    while ((dent = readdir(dir)) != NULL)
    {
        if (dent->d_name[0] == '.'  &&
           (dent->d_name[1] == '\0' ||
           (dent->d_name[1] == '.'  &&
           dent->d_name[2] == '\0'
        )))
            continue;

        snprintf(fpath, sizeof(fpath), "%s/%s", path, dent->d_name);

        if (access(fpath, X_OK) == 0)
        {
            writebuf(dent->d_name);
            writebuf("*");
            writebuf("\t");
        }

        else
        {
            writebuf(dent->d_name);
            writebuf("\t");
        }
    }

    closedir(dir);
}
#else
    // TODO: Windows implementation
    // ...
#endif
