#include <iostream>
#include <filesystem>
#include <ncurses.h>

#include "io.hpp"

void LoadDir(std::vector<Directory> &Dir, std::vector<std::string> path)
{
    std::string pathTEMP;
    for (int i = 0; i < path.size(); i++)
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
    
        if(e.code().value() == 13)
        

        mvprintw(getmaxy(stdscr) - 1, 0, "Error: permission denied");
        refresh();
    }
}

void StringToPath(std::string path, std::vector<std::string> &pathV)
{
    pathV.clear();
    std::string temp = "";
    for (int i = 0; i < path.length(); ++i)
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