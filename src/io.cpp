#include <iostream>
#include <filesystem>
#include <ncurses.h>

#include "io.hpp"

void LoadDir(std::vector<Directory> &Dir, std::vector<std::string> path)
{
    std::string pathTEMP;
    for (size_t i = 0; i < path.size(); i++)
    {
        pathTEMP += path[i];
    }

    Dir.clear();
    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(pathTEMP))
        {
            Directory temp;
            if (entry.is_directory())
                temp.fileType = "dir";
            else if (entry.is_regular_file())
                temp.fileType = "file";
            else
                temp.fileType = "error";
            temp.file = entry.path().filename();
            Dir.push_back(temp);
        }
    }
    catch (std::filesystem::filesystem_error &e)
    {
        std::error_code b;

        if (e.code().value() == 13)

            mvprintw(getmaxy(stdscr) - 1, 0, "Error: permission denied");
        refresh();
    }
}

void StringToPath(std::string path, std::vector<std::string> &pathV)
{
    pathV.clear();
    std::string temp = "";
    for (size_t i = 0; i < path.length(); ++i)
    {

        if (path[i] == '/')
        {
            pathV.push_back("/" + temp);
            temp = "";
        }
        else
        {
            temp.push_back(path[i]);
        }
    }
    pathV.push_back(temp);
}

std::string PathToString(const std::vector<std::string> &pathV)
{
    std::string result;
    for (size_t i = 0; i < pathV.size(); i++)
        result += pathV[i];
    return result;
}

std::string runCommand(std::string command, std::string currentPath)
{
    char buffer[128];
    std::string result = "";
    command = "bash -c \' cd " + currentPath + " 2</dev/null ; "+ command + " 2</dev/null\'";
    // Open pipe to file
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        return "ERROR: cannot run command";
    }

    // read till end of process:
    while (!feof(pipe))
    {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

void runApp(std::string file)
{
    std::vector<std::string> fileV;
    std::string temp = "";
    for (size_t i = 0; i < file.length(); ++i)
    {

        if (file[i] == '.')
        {
            fileV.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(file[i]);
        }
    }
    fileV.push_back(temp);
    if(fileV[fileV.size() - 1] == "txt")
        system("vim");
}