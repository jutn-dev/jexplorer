#pragma once
#include <iostream>
#include <vector>

struct File
{
    std::string fileType;
    std::string file;
    std::string path;
};

// loads directory
void LoadDir(std::vector<File> &Dir, std::vector<std::string> path);

void StringToPath(std::string path, std::vector<std::string> &pathV);

std::string PathToString(const std::vector<std::string> &pathV);

std::string runCommand(std::string command, std::string currentPath);

void runApp(File file);
