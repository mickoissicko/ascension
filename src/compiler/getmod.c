#include <stddef.h>

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
