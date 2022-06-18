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
    

    int choice;
    while (true)
    {
        getmaxyx(stdscr, endY, endX);
        if (oldendX != endX || oldendY != endY)
        {
            clear();

            filesWin.resize(endY - 2, endX - 4, true);
        }

        filesWin.printMenu(Dir);

        choice = wgetch(filesWin.win);

        switch (choice)
        {
        case KEY_UP:
            filesWin.scroll--;
            break;

        case KEY_DOWN:
            filesWin.scroll++;

        default:
            break;
        }
        if (choice == 10)
        {
            LoadDir(Dir, path);
            wclear(filesWin.win);
        }

        if (filesWin.highlighted < 0)
            filesWin.highlighted = 0;
        if (filesWin.highlighted > Dir.size())
            filesWin.highlighted = Dir.size() - 1;

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
