#include <stdlib.h>
#include <string.h>

#define BUF 512

char* PrintOS()
{
    char* OperatingSystem;
    OperatingSystem = (char*)malloc(BUF * sizeof(char));

    #ifdef _WIN32
        #ifdef _WIN64
            strcpy(OperatingSystem, "Windows-x64")
        #else
            strcpy(OperatingSystem, "Windows-x86");
    #endif

    #elif defined(__CYGWIN__)
        strcpy(OperatingSystem, "CYGWIN");

    #elif defined(__unix__) || defined(unix) || defined(__unix)
        strcpy(OperatingSystem, "Unix-based (or *BSD)");

    #elif defined(__APPLE__) && defined(__MACH__)
        strcpy(OperatingSystem, "Mac OS");

    #elif defined(linux)
        strcpy(OperatingSystem, "Linux");

    #elif defined(__FreeBSD__)
        strcpy(OperatingSystem, "FreeBSD");

    #elif defined(__ANDROID__)
        strcpy(OperatingSystem, "Android");

    #elif defined(__linux__) || defined(__linux)
        strcpy(OperatingSystem, "?");
    #endif

    return OperatingSystem;
}

