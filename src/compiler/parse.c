#define STD_WRITE
#define VAR
#define IO

#include "../shared/incl.h"
#include "../std/io.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
                        return _throw(var(0), var(3));

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
                    if (!sys) return _throw(var(7), var(3));
                    if (strcmp(ln + _sz, F_END) == 0) break;

                    char buf[sizeof(ln)];
                    int buf_i = 0;
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

                    buf[buf_i] = '\0';
                    cd(buf);
                }

                if (strncmp(ln + (_sz + _sz), var(1), strlen(var(1))) == 0)
                {
                    if (!io)
                        return _throw(var(1), var(2));

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
