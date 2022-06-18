#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>

#include "io.hpp"

struct window
{
    public:
    window(int sizeY, int sizeX, int posY, int posX);

    void resize(int sizeY, int sizeX, bool withBox);

    void update();

    void printMenu(std::vector<Directory> Dir);

    //Doesn't exist
    void printMenu(std::vector<std::string> stuff);

    WINDOW *win;

    int highlighted = 0;
    int scroll = 0;

    int beginX, beginY, endX, endY;
    int oldbeginX, oldbeginY, oldendX, oldendY;
};
