#include <stdio.h>

void PrintOS()
{
    #ifdef _WIN32
        #ifdef _WIN64
            printf("Windows x64\n");
        #else
            printf("Windows x86\n");
    #endif

    #elif defined(__CYGWIN__)
        printf("CYGWIN\n");

    #elif defined(__unix__) || defined(unix) || defined(__unix)
        printf("Unix or *BSD\n");

    #elif defined(__APPLE__) && defined(__MACH__)
        printf("Mac OS\n");

    #elif defined(linux)
        printf("Linux\n");

    #elif defined(__FreeBSD__)
        printf("FreeBSD\n");

    #elif defined(__ANDROID__)
        printf("Android\n");

    #elif defined(__linux__) || defined(__linux)
        printf("Unknown\n");
    #endif
}

