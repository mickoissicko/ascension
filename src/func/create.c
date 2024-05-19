#include <string.h>
#include <stdio.h>

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

void Mkd()
{}

