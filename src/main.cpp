#include <iostream>
#include <ncurses.h>
#include <filesystem>
#include <vector>

#include "io.hpp"
#include "window.hpp"

// void bb(char b);

int main(int argc, char* argv[])
{

    std::string path = "/";

    if(argc > 1)
    {
        path = argv[1];
    }

    std::vector<Directory> Dir;
    LoadDir(Dir, path);
    // init("bbb");
    // loadDir(3);

    initscr();
    cbreak();
    noecho();

    int beginX, beginY, endX, endY;
    int oldbeginX, oldbeginY, oldendX, oldendY;
    getbegyx(stdscr, beginY, beginX);
    getmaxyx(stdscr, endY, endX);

    window filesWin(endY - 2, endX - 4, beginY + 1, beginX + 2);

    //WINDOW *filesWin = newwin(endY - 2, endX - 4, beginY + 1, beginX + 2);
    keypad(filesWin.win, true);
    box(filesWin.win, 0, 0);
    // mvwprintw(filesWin,2, 2, "Wau!");
    
    int highlighted = 0;
    int scroll = 0;
    int choice;
    while (true)
    {
        getmaxyx(stdscr, endY, endX);
        if (oldendX != endX || oldendY != endY)
        {
            clear();

            filesWin.resize(endY - 2, endX - 4, true);
        }

        wclear(filesWin.win);
        box(filesWin.win, 0, 0);
        for (int i = 0 + scroll; i < Dir.size(); i++)
        {

            if (i + scroll == highlighted)
                wattron(filesWin.win, A_REVERSE);
            mvwprintw(filesWin.win, i + 1 - scroll, 1, "%s %s", Dir[i].fileType.c_str(), Dir[i].file.c_str());
            wattroff(filesWin.win, A_REVERSE);
        }
        choice = wgetch(filesWin.win);

        switch (choice)
        {
        case KEY_UP:
            scroll--;
            break;

        case KEY_DOWN:
            scroll++;

        default:
            break;
        }
        if (choice == 10)
        {
            LoadDir(Dir, path);
            wclear(filesWin.win);
        }

        if (highlighted < 0)
            highlighted = 0;
        if (highlighted > Dir.size())
            highlighted = Dir.size() - 1;

        oldendX = endX;
        oldendY = endY;
        oldbeginX = beginX;
        oldbeginY = beginY;
    }

    refresh();
    getch();
    
    endwin();

    return 0;
}
