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

/*
 *   @brief  Load Directory
 *   @param  Dir directory
 *   @param  path path to directory
 */
void LoadDir(std::vector<File> &Dir, std::vector<std::string> path);

// load configuration file
void LoadConfig();


void StringToPath(std::string path, std::vector<std::string> &pathV);

std::string PathToString(const std::vector<std::string> &pathV);

void splitStringToVector(std::string string, std::vector<std::string> &vector, char splitter);

/*
 *   @brief  Run command from current directory 
 *   @param  comamnd Terminal command
 *   @param currentPath current path
 */
std::string runCommand(std::string command, std::string currentPath);

/*
 *   @brief  opens file in application
 *   @param  file file
 */
void runApp(File file);
