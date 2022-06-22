#include <iostream>
#include <ncurses.h>

#include "windows.hpp"
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


