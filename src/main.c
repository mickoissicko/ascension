#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXBUF 8192
#define INPUT 4096

static char* gethome();
char* ConcatenateCWD(char Cwd[MAXBUF]);

const char Start = '~';

int main(int argc, char** argv)
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
        strcat(Path, &Start);

        printf("%s\n", Path);
        fgets(Ui, INPUT, stdin);

        if (!!strcmp(Ui, "") || !!strcmp(Ui, NULL))
            ParseCommands();
    }

    //main(argc, argv);
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
        return CCwd;

    return CCwd;
}

#ifdef __WIN32__
    static char* gethome()
    {
        unsigned long LEN = MAX_STR_LEN;

        char* HomeDirectory = getenv("USERPROFILE");

        return HomeDirectory;
    }
#else
    #include <pwd.h>
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

