#pragma once
#include <iostream>
#include <ncurses.h>

struct window
{
    public:
    window(int sizeY, int sizeX, int posY, int posX);

    void resize(int sizeY, int sizeX, bool withBox);

    void update();

    WINDOW *win;

    int beginX, beginY, endX, endY;
    int oldbeginX, oldbeginY, oldendX, oldendY;
};
