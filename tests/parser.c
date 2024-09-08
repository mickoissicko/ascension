#ifndef _WIN32
#include <sys/stat.h>
#include <dirent.h>
#endif
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_INDENT_SZ 4
#define INCL "include "
#define BEGIN "begin."
#define ENTRY "begin def start"
#define F_END "end"
#define VIA "via "
#define ATH "ath."
#define END "end."
#define DEF "def "

char* var(int var)
{
    if (var == 0) return "sysrun";
    if (var == 1) return "echo ";
    if (var == 2) return "Std::IO.";
    if (var == 3) return "Std::System.";
    if (var == 4) return "ls";
    if (var == 5) return "ls ";
    if (var == 6) return "!indent_sz";
    if (var == 7) return "cd ";

    return NULL;
}

int checklsarg(const char program[])
{
    if (strncmp(program, var(5), strlen(var(5))) == 0) return 1;
    else return 0;

    return -1;
}

int throw(char var1[], char var2[])
{
    printf("`%s` not found\n", var1);
    printf("Did you forget to include `%s`?\n", var2);
    return 1;
}

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

        if (access(fpath, X_OK))
            printf("%s\t", dent->d_name);

        else
            printf("%s*\t", dent->d_name);
    }

    closedir(dir);
}

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

int getindentsz(char f[])
{
    char ln[8192];

    int ln_exists = 0;
    int i = 0;
    int _i;

    FILE* fp = fopen(f, "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    while (fgets(ln, sizeof(ln), fp) != NULL && i < 2)
    {
        if (strncmp(ln, var(6), strlen(var(6))) == 0)
        {
            for (_i = 0; ln[_i] != '\0'; _i++)
                if (ln[_i] == '=')
                {
                    if (ln[_i + 1] == ' ')
                        _i += 2;

                    else
                        _i += 1;
                }

            ln_exists = 1;
        }

        else ln_exists = 0;

        i++;
    }

    ln[strcspn(ln, "\n")] = '\0';

    fclose(fp);

    if (!ln_exists) return DEFAULT_INDENT_SZ;
    else return atoi((ln + _i) - 2);
}

int parse(FILE* fp, int _sz)
{
    rewind(fp);

    char ln[8192];
    int count = 0;
    int excl = 0;
    int sys = 0;
    int io = 0;

    while (fgets(ln, sizeof(ln), fp) != NULL)
    {
        ln[strcspn(ln, "\n")] = '\0';

        if (excl == 0)
        {
            char buf[(sizeof(ln) / 2)];
            int noexec = 0;
            rewind(fp);
            excl = 1;

            while (count < 3)
            {
                if (fgets(buf, sizeof(buf), fp) != NULL)
                    if (strncmp(buf, var(6), strlen(var(6))) == 0)
                    {
                        noexec = 1;

                        if (fgets(buf, sizeof(buf), fp) == NULL)
                        {
                            printf("No `begin.` block.\n");
                            return 1;
                        }
                    }

                count++;
            }

            buf[0] = '\0';
            rewind(fp);
            count = 0;

            while (count < 2 && noexec == 0)
            {
                if (fgets(buf, sizeof(buf), fp) != NULL)
                {
                    buf[strcspn(buf, "\n")] = '\0';

                    if (count == 1 && strcmp(buf, BEGIN) != 0)
                    {
                        printf("No `begin.` block.\n");
                        return 1;
                    }
                }

                count++;
            }
        }

        if (strstr(ln, INCL) != NULL)
        {
            if (strcmp(ln + strlen(INCL) + _sz, var(3)) == 0)
                sys = 1;

            if (strcmp(ln + strlen(INCL) + _sz, var(2)) == 0)
                io = 1;
        }

        if (strcmp(ln + _sz, ENTRY) == 0)
        {
            while (fgets(ln, sizeof(ln), fp) != NULL)
            {
                char program[1024];
                int paren_count = 0;

                ln[strcspn(ln, "\n")] = '\0';

                if (strcmp(ln + _sz, F_END) == 0) break;
                if (strncmp(ln + (_sz + _sz), var(0), strlen(var(0))) == 0)
                {
                    if (!sys)
                        return throw(var(0), var(3));

                    if (strchr(ln, '(') != NULL)
                    {
                        int pstart = strchr(ln, '(') - ln + 1;
                        strncpy(program, ln + pstart, sizeof(program) - 1);

                        program[sizeof(program) - 1] = '\0';
                        char *qend = strrchr(program, '"');

                        if (qend)
                            *qend = '\0';

                        char *qstart = strchr(program, '"');

                        if (qstart)
                            memmove(program, qstart + 1, strlen(qstart));

                        char *pend = strrchr(program, ')');

                        if (pend)
                            *pend = '\0';

                        size_t len = strlen(program);

                        if (len > 0 && program[len - 1] == '.')
                            program[len - 1] = '\0';

                        if (strstr(program, var(4)) != NULL)
                        {
                            int lsarg = checklsarg(program);

                            if (lsarg)
                            {
                                char* fullpath = (char*)malloc(sizeof(char) * 4096);
                                strcpy(fullpath, (program + strlen(var(5))));
                                ls(fullpath);
                                free(fullpath);
                            }

                            else ls(".");
                        }

                        else exec(program);
                    }
                }

                if (strncmp(ln + (_sz + _sz), var(7), strlen(var(7))) == 0)
                {
                    if (!sys) return throw(var(7), var(3));
                    if (strcmp(ln + _sz, F_END) == 0) break;

                    char buf[sizeof(ln)];
                    int buf_i;
                    int qstat = 0;

                    for (int i = 0; i < strlen(ln); i++)
                    {
                        if (ln[i] == '\'' || ln[i] == '"')
                            qstat = !qstat;

                        else if (qstat)
                        {
                            if (ln[i] == '\\' && ln[(i + 1)] == 'n')
                            {
                                buf[buf_i++] = '\n';
                                i++;
                            }

                            else buf[buf_i++] = ln[i];
                        }
                    }

                    chdir(buf);
                }

                if (strncmp(ln + (_sz + _sz), var(1), strlen(var(1))) == 0)
                {
                    if (!io) return throw(var(1), var(2));
                    if (strcmp(ln + _sz, F_END) == 0) break;

                    int qstat = 0;
                    
                    for (int i = 0; i < strlen(ln); i++)
                    {
                        if (ln[i] == '\'' || ln[i] == '"')
                            qstat = !qstat;
                        
                        else if (qstat)
                        {
                            if (ln[i] == '\\' && ln[(i + 1)] == 'n')
                            {
                                putchar('\n');
                                i++;
                            }

                            else
                                putchar(ln[i]);
                        }
                    }
                }

                count++;
            }
        }

        count++;
    }

    return 0; // OK
}

void getsh(FILE* fp, char file[])
{
    char* ln = (char*)malloc(sizeof(char) * 1024);
    if (ln == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int _sz = getindentsz(file);
    int ln_count = 0;
    int via = 0;

    while (fgets(ln, 1024, fp) != NULL)
    {
        ln[strcspn(ln, "\n")] = '\0';

        if (strstr(ln, VIA) != NULL)
        {
            via = 1;

            if (strcmp(ln + strlen(VIA), ATH) == 0)
                parse(fp, _sz);

            else
            {
                printf("Other shells are not supported at this point\n");
                free(ln);
                return;
            }
        }

        ln_count++;
    }

    if (!via)
        printf("Missing `via` directive\n");

    free(ln);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    getsh(fp, argv[1]);
    fclose(fp);
    return 0;
}
