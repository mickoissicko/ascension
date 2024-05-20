#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define UNINITIALISED -1
#define MAX_BUF 4096

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
        Mode == UNINITIALISED &&
        !strncmp(String, "mkf", 3) ||
        !strncmp(String, "mkd", 3)
    ){
        printf("No (valid) mode provided\n");
        return;
    }

    else if (Mode == UNINITIALISED)
    {
        printf("Will use 0\n");
        Mode = 0;
    }

    if (
        Mode > 1 &&
        !strncmp(String, "mkf", 3) ||
        !strncmp(String, "mkd", 3) 
    ){
        printf("Currently two modes available:\n");
        printf("1: Overwrite\n");
        printf("0: Passive\n");
        return;
    }

    else if (
        Mode > 2 &&
        !strncmp(String, "rmd", 3) ||
        !strncmp(String, "rmf", 3)
    ){
        printf("Currently three modes available\n");
        printf("2 (rmd): Recursively delete\n");
        printf("1: Delete without prompt\n");
        printf("0: Default if unspecified\n");
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

