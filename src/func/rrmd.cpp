#include <filesystem>

void RRmd(char Filename[])
{
    std::filesystem::remove_all(Filename);
}

