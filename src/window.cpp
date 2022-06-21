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
    // if (p_withBox)
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

void window::input(int choice, int listSize, std::vector<Directory> &Dir, std::vector<std::string> &path)
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

void window::printMenu(std::vector<Directory> p_Dir)
{
    werase(win);
    box(win, 0, 0);
    for (int i = 0 + scroll; i < p_Dir.size(); i++)
    {
        if (i - scroll > sizeY - 3)
            break;

        if (i == highlighted)
            wattron(win, A_REVERSE);
        mvwprintw(win, i + 1 - scroll, 1, "%s %s", p_Dir[i].fileType.c_str(), p_Dir[i].file.c_str());
        wattroff(win, A_REVERSE);
    }
}
