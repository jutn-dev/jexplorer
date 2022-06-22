#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>

#include "io.hpp"

class window
{
public:
    window(int p_sizeY, int p_sizeX, int p_posY, int p_posX);

    void resize(int p_sizeY, int p_sizeX, int p_posY, int p_posX, bool p_withBox);

    virtual void update();

    WINDOW *win;

    int sizeY, sizeX;

    int beginX, beginY;
    int oldbeginX, oldbeginY;
};

class MenuWindow : public window
{
public:
    MenuWindow(int p_sizeY, int p_sizeX, int p_posY, int p_posX);

    void input(int choice, int listSize, std::vector<Directory> &Dir, std::vector<std::string> &path);

    void printMenu(std::vector<Directory> p_Dir);

    // Doesn't exist
    void printMenu(std::vector<std::string> p_stuff);

private:
    int highlighted = 0;
    int scroll = 0;
};

class TerminalWindow : public window
{
public:
    TerminalWindow(int p_sizeY, int p_sizeX, int p_posY, int p_posX);

    void input(int input, std::string path);

    bool TerminalMode = false;
    std::string command;
};

class TextWindow : public window
{
public:
    TextWindow(std::string p_Text ,int p_sizeY, int p_sizeX, int p_posY, int p_posX);

    void setText(std::string moreText);

    std::string Text;
};
