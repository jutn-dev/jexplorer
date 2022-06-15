#include <iostream>
#include <filesystem>

#include "io.hpp"

void LoadDir(std::vector<Directory> &Dir, std::string path)
{
    Dir.clear();
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        Directory temp;
        if(entry.is_directory())
            temp.fileType = "dir";
        else if(entry.is_regular_file())
            temp.fileType = "file";
        else
            temp.fileType = "error";
        temp.file = entry.path().filename();
        Dir.push_back(temp);
    }
}
