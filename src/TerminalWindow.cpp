#include <iostream>
#include <ncurses.h>

#include "windows.hpp"

// terminal window
TerminalWindow::TerminalWindow(int p_sizeY, int p_sizeX, int p_posY, int p_posX)
    : window(p_sizeY, p_sizeX, p_posY, p_posX) {}

void TerminalWindow::input(int input, std::string path)
{
    if (input == 10)
    {
        std::string result = runCommand(command, path);
        if (result == "")
            mvwprintw(win, sizeY - 1, 0, "Error: command failed to execute");
        else
        {
            mvwprintw(win, sizeY - 1, 0, "%s", result.c_str());
        }
    }
    else
    {
        command += (char)input;
        mvwprintw(win,sizeY - 2, 1, "%s", command.c_str());
    }
    if (input == 27) // 27 == esc
    {
        TerminalMode = false;
        wclear(win);
        wrefresh(win);
    }
}