#pragma once
#include <iostream>
#include <vector>

struct Directory
{
    std::string fileType;
    std::string file;
};


//loads directory
void LoadDir(std::vector<Directory> &Dir, std::string path);
