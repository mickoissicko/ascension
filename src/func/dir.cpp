#include <filesystem>
#include <unistd.h>
#include <iostream>

namespace Fs = std::filesystem;

#define MAX_LEN 8192

void Ls()
{
    char Path[MAX_LEN];
    getcwd(Path, sizeof(Path));

    for (const auto & List : Fs::directory_iterator(Path))
        std::cout << List.path() << '\n';
}

