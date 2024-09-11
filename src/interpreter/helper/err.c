#include <stdio.h>

int _throw(char var1[], char var2[])
{
    printf("`%s` not found\n", var1);
    printf("Did you forget to include `%s`?\n", var2);
    return 1;
}
