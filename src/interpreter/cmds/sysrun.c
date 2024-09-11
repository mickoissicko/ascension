#include <unistd.h>
#include <stdio.h>
#ifndef _WIN32
#include <sys/wait.h>
void exec(char program[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Could not fork");
        return;
    }

    else if (pid == 0)
    {
        char* args[] = {program, NULL};
        execv(args[0], args);

        perror("Error executing");
        return;
    }

    else
    {
        int stat;
        waitpid(pid, &stat, 0);

        if (!WIFEXITED(stat))
            printf("exit via %d\n", stat);
    }
}
#else
    // TODO: Windows implementation
    // ...
#endif
