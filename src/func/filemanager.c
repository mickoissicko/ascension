#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define UNINITIALISED -1
#define MAX_BUF 4096

void RRmd(char Filename[]);
void Rmf(char Filename[], int Mode)
{
    char Ui;

    if (Mode == 0)
    {
        printf("Delete file? [y/n]: ");
        scanf(" %c", &Ui);

        if (!strcasecmp(&Ui, "y"))
            if (remove(Filename) != 0)
            {
                perror("Could not delete file");
                return;
            }
    }

    if (Mode == 1)
        if (remove(Filename) != 0)
        {
            perror("Could not delete file");
            return;
        }
}

void Rmd(char Filename[], int Mode)
{
    char Ui;

    if (Mode == 0)
    {
        printf("Delete file? [y/n]: ");
        scanf(" %c", &Ui);

        if (!strcasecmp(&Ui, "y"))
            if (rmdir(Filename) != 0)
            {
                perror("Could not delete file");
                return;
            }
    }

    if (Mode == 1)
        if (rmdir(Filename) != 0)
        {
            perror("Could not delete file");
            return;
        }

    if (Mode == 2)
        RRmd(Filename);
}

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
        File = fopen(Filename, "r");

        if (File != NULL)
        {
            fclose(File);
            printf("File already exists!\n");
            return;
        }
    
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
    int Mode = UNINITIALISED;

    char Filename[MAX_BUF];
    char Discard[MAX_BUF];
    char Ui;

    sscanf(String, "%s %s %d", Discard, Filename, &Mode);

    if (
        !strncmp(String, "mkf", 3) ||
        !strncmp(String, "mkd", 3) ||
        !strncmp(String, "rmf", 3)
    )
        if (Mode == UNINITIALISED || Mode > 1)
        {
            char Cmd[] = {[0]=String[0], [1]=String[1], [2]=String[2]};
        
            printf("Invalid mode\n");
            printf("%s (filename) [0-1]\n", Cmd);

            return;
        }

    else if (!strncmp(String, "rmd", 3))
        if (Mode == UNINITIALISED || Mode > 2)
        {
            printf("Invalid mode\n");
            printf("rmd (dirname) [0-2]\n");

            return;
        }

    if (!strncmp(String, "mkf", 3))
        Mkf(Filename, Mode);

    if (!strncmp(String, "mkd", 3))
        Mkd(Filename, Mode);

    if (!strncmp(String, "rmf", 3))
        Rmf(Filename, Mode);

    if (!strncmp(String, "rmd", 3))
        Rmd(Filename, Mode);
}

