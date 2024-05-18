#include "include/common.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    printf("Welcome to the Ascension Shell\n");
    printf("Type help for a list of commands\n");

    Shell(argc, argv);
    return 0;
}

