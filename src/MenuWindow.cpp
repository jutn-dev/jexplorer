#include <iostream>
#include <ncurses.h>

#include "io.hpp"
#include "windows.hpp"

MenuWindow::MenuWindow(int p_sizeY, int p_sizeX, int p_posY, int p_posX)
    : window(p_sizeY, p_sizeX, p_posY, p_posX) {}

void MenuWindow::input(int choice, int listSize, std::vector<File> &Dir, std::vector<std::string> &path)
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
        else
        {
            runApp(Dir[highlighted]);
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

void MenuWindow::printMenu(std::vector<File> p_Dir)
{
    werase(win);
    box(win, 0, 0);
    for (size_t i = 0 + scroll; i < p_Dir.size(); i++)
    {
        if (i - scroll > sizeY - 3)
            break;

        if (i == highlighted)
            wattron(win, A_REVERSE);
        if (p_Dir[i].fileType == "dir")
            wattron(win, COLOR_PAIR(1));

        mvwprintw(win, i + 1 - scroll, 1, "%s", p_Dir[i].fileType.c_str());
        wattroff(win, COLOR_PAIR(1));
        wprintw(win, "  %s", p_Dir[i].file.c_str());

        wattroff(win, A_REVERSE);
    }
}