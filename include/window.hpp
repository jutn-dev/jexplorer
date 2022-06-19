#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>

#include "io.hpp"

struct window
{
    public:
    window(int p_sizeY, int p_sizeX, int p_posY, int p_posX);

    void resize(int p_sizeY, int p_sizeX, bool p_withBox);

    void update();

    void printMenu(std::vector<Directory> p_Dir);

    //Doesn't exist
    void printMenu(std::vector<std::string> p_stuff);

    WINDOW *win;

    int sizeY, sizeX;

    int highlighted = 0;
    int scroll = 0;

    int beginX, beginY, endX, endY;
    int oldbeginX, oldbeginY, oldendX, oldendY;
};
