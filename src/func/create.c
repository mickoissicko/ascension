#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_BUF 4096

void Mkf(char Filename[], int Mode)
{
    if (Mode == 0)
    {
        if (Filename == NULL || !strcmp(Filename, ""))
        {
            printf("Specify a valid filename\n");
            return;
        }

        FILE* File;
        File = fopen(Filename, "w");

        if (File != NULL)
            fclose(File);
        else
            perror("Could not make file");
    }

    else if (Mode == 1)
    {
        FILE* File;
        File = fopen(Filename, "w");

        if (File != NULL)
            fclose(File);

        else
        {
            if (remove(Filename) != 0)
            {
                perror("Error removing");
                return;
            }

            File = fopen(Filename, "w");

            if (File != NULL)
                fclose(File);

            else
            {
                perror("Could not make file");
                return;
            }
        }
    }
}

void Mkd(char Directory[], int Mode)
{
    if (Mode == 0)
    {
        if (mkdir(Directory, 0777) != 0)
        {
            perror("Could not make directory");
            return;
        }

        else
            printf("Made %s\n", Directory);
    }

    else if (Mode == 1)
    {
        if (mkdir(Directory, 0777) != 0)
        {
            if (rmdir(Directory) != 0)
            {
                perror("Error removing");
                return;
            }

            else
            {
                if (mkdir(Directory, 0777) != 0)
                {
                    perror("Could not make");
                    return;
                }

                printf("Made %s\n", Directory);
            }
        }
    }
}

void PrepareForCreation(char String[])
{
    char Discard[MAX_BUF];
    char Filename[MAX_BUF];
    int Mode;

    sscanf(String, "%s %s %d", Discard, Filename, &Mode);

    if (Mode > 1)
    {
        printf("Currently two modes available:\n");
        printf("1: Overwrite\n");
        printf("0: Passive\n");
    }

    if (!strncmp(String, "mkf", 3))
        Mkf(Filename, Mode);

    if (!strncmp(String, "mkd", 3))
        Mkd(Filename, Mode);
}

