#pragma once
#include <iostream>
#include <vector>

struct Directory
{
    std::string fileType;
    std::string file;
};


//loads directory
void LoadDir(std::vector<Directory> &Dir, std::vector<std::string> path);

void StringToPath(std::string path, std::vector<std::string> &pathV);
