#pragma once
#include <iostream>
#include <vector>

struct File
{
    std::string fileType;
    std::string file;
    std::string path;
    bool hidden;
};

// loads directory
void LoadDir(std::vector<File> &Dir, std::vector<std::string> path);

void LoadConfig();

void StringToPath(std::string path, std::vector<std::string> &pathV);

std::string PathToString(const std::vector<std::string> &pathV);

void splitStringToVector(std::string string, std::vector<std::string> &vector, char splitter);

std::string runCommand(std::string command, std::string currentPath);

void runApp(File file);
