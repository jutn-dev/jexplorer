#include <iostream>
#include <ncurses.h>

#include "window.hpp"
// winidow class
window::window(int p_sizeY, int p_sizeX, int p_posY, int p_posX)
    : sizeY(p_sizeY), sizeX(p_sizeX), beginX(p_posX), beginY(p_posY)
{
    win = newwin(p_sizeY, p_sizeX, p_posY, p_posX);
}

void window::resize(int p_sizeY, int p_sizeX, int p_posY, int p_posX, bool p_withBox)
{

    wclear(win);
    wresize(win, p_sizeY, p_sizeX);
    mvwin(win, p_posY, p_posX);
    if (p_withBox)
        box(win, 0, 0);
    refresh();
    wrefresh(win);

    sizeY = p_sizeY;
    sizeX = p_sizeX;
}

void window::update()
{
    oldbeginX = beginX;
    oldbeginY = beginY;
}

// Menu window
MenuWindow::MenuWindow(int p_sizeY, int p_sizeX, int p_posY, int p_posX)
    : window(p_sizeY, p_sizeX, p_posY, p_posX) {}
// input
void MenuWindow::input(int choice, int listSize, std::vector<Directory> &Dir, std::vector<std::string> &path)
{
    switch (choice)
    {
    case KEY_UP:
        if (highlighted > 0)
        {
            highlighted--;
            if (-1 == highlighted - scroll)
                scroll--;
        }
        break;

    case KEY_DOWN:
        if (highlighted < listSize - 1)
        {
            highlighted++;
            if (highlighted - scroll - sizeY == -2)
                scroll++;
        }
        break;

    default:
        break;
    }

    if (highlighted < 0)
        highlighted = 0;
    if (highlighted > listSize)
        highlighted = listSize - 1;

    if (choice == KEY_RIGHT)
    {
        if (Dir[highlighted].fileType == "dir")
        {

            path.push_back(Dir[highlighted].file + '/');
            wclear(win);
            LoadDir(Dir, path);
            box(win, 0, 0);
            scroll = 0;
            highlighted = 0;
        }
    }

    if (choice == KEY_LEFT)
    {
        if (path.size() > 1)
        {
            path.pop_back();
            wclear(win);
            LoadDir(Dir, path);
            box(win, 0, 0);
            scroll = 0;
            highlighted = 0;
        }
    }
}

void MenuWindow::printMenu(std::vector<Directory> p_Dir)
{
    werase(win);
    box(win, 0, 0);
    for (size_t i = 0 + scroll; i < p_Dir.size(); i++)
    {
        if (i - scroll > sizeY - 3)
            break;

        if (i == highlighted)
            wattron(win, A_REVERSE);
        if(p_Dir[i].fileType == "dir")
            wattron(win, COLOR_PAIR(1));

        mvwprintw(win, i + 1 - scroll, 1, "%s", p_Dir[i].fileType.c_str());
        wattroff(win, COLOR_PAIR(1));
        wprintw(win, "  %s" ,p_Dir[i].file.c_str());

        wattroff(win, A_REVERSE);
    }
}

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