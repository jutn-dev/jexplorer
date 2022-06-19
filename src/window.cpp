#include <iostream>
#include <ncurses.h>

#include "window.hpp"

window::window(int p_sizeY, int p_sizeX, int p_posY, int p_posX)
{
    win = newwin(p_sizeY, p_sizeX, p_posY, p_posX);

    getbegyx(win, beginY, beginX);
    getmaxyx(win, endY, endX);

    sizeY = p_sizeY;
    sizeX = p_sizeX;
}

void window::resize(int p_sizeY, int p_sizeX, bool p_withBox)
{

    wclear(win);
    wresize(win, p_sizeY, p_sizeX);
    if (p_withBox)
        box(win, 0, 0);
    refresh();
    wrefresh(win);

    sizeY = p_sizeY;
    sizeX = p_sizeX;
}

void window::update()
{
    oldendX = endX;
    oldendY = endY;
    oldbeginX = beginX;
    oldbeginY = beginY;
}

void window::printMenu(std::vector<Directory> p_Dir)
{
    wclear(win);
    for (int i = 0 + scroll; i < p_Dir.size(); i++)
    {
        if (i == highlighted)
            wattron(win, A_REVERSE);
        mvwprintw(win, i + 1 - scroll, 1, "%s %s", p_Dir[i].fileType.c_str(), p_Dir[i].file.c_str());
        wattroff(win, A_REVERSE);
    }
    box(win, 0, 0);
}
