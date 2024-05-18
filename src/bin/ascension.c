#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXBUF 8192
#define INPUT 4096

static char* gethome();
char* ConcatenateCWD(char Cwd[MAXBUF]);
void Parser(char Str[MAXBUF]);

const char Start[] = "~/";

int Shell(int argc, char** argv)
{
    printf("Welcome to the Ascension Shell\n");
    printf("Type help for a list of commands\n");

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

        memmove(Path + 1, Path, strlen(Path));
        strncpy(Path, Start, 2); 

        printf("%s\n", Path);
        printf("> ");

        fgets(Ui, INPUT, stdin);
        Ui[strcspn(Ui, "\n")] = 0;

        Parser(Ui);
    }

    //main(argc, argv);
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
        printf("exit: close the shell\n");
    }

    if (!strcmp(Str, "exit"))
        exit(0);
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

