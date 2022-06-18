#include <iostream>
#include <ncurses.h>

#include "window.hpp"

window::window(int sizeY, int sizeX, int posY, int posX)
{
    win = newwin(sizeY, sizeX, posY, posX);

    getbegyx(win, beginY, beginX);
    getmaxyx(win, endY, endX);
}

void window::resize(int sizeY, int sizeX, bool withBox)
{
    wclear(win);
    wresize(win, sizeY, sizeX);
    if (withBox)
        box(win, 0, 0);
    refresh();
    wrefresh(win);
}

void window::update()
{
    oldendX = endX;
    oldendY = endY;
    oldbeginX = beginX;
    oldbeginY = beginY;
}

void window::printMenu(std::vector<Directory> Dir)
{
    wclear(win);
    box(win, 0, 0);
    for (int i = 0 + scroll; i < Dir.size(); i++)
    {
        if (i + scroll == highlighted)
            wattron(win, A_REVERSE);
        mvwprintw(win, i + 1 - scroll, 1, "%s %s", Dir[i].fileType.c_str(), Dir[i].file.c_str());
        wattroff(win, A_REVERSE);
    }
}
