#ifndef COMMON_H
    #define COMMON_H
#endif

#define PATH_LEN 8192

#ifdef __WIN32__
    #include <stdlib.h>
    #include <stdio.h>

    static char* gethome()
    {
        unsigned long LEN = MAX_STR_LEN;

        char* HomeDirectory = getenv("USERPROFILE");

        return HomeDirectory;
    }
#else
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <pwd.h>

    #define MAXBUF 8192
    static char* gethome()
    {
        struct passwd *Home;

        char* Path = NULL;

        if ((Home = getpwuid(getuid())) != NULL)
        {
            Path = (char*)malloc(MAXBUF);

            if (Path != NULL)
                strcpy(Path, Home->pw_dir);
        }

        return Path;
    }
#endif

void PrepareForCreation(char String[]);
void DirSwitcher(char Dir[]);
static char* gethome();
int Shell(int argc, char** argv);
void Parser(char Str[MAXBUF]);
void ClearScreen(char Str[]);
char* PrintOS();
void Mkf();
void Mkd();
void Ls();

