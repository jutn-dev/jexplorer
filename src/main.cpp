#include <iostream>
#include <ncurses.h>
#include <filesystem>
#include <vector>

#include "io.hpp"
#include "window.hpp"

// void bb(char b);
int main(int argc, char *argv[])
{
    // std::string homePath = getenv("HOME");
    std::vector<std::string> path;
    path.push_back("/");

    if (argc > 1)
    {
        StringToPath(argv[1], path);
    }

    std::vector<Directory> Dir;
    LoadDir(Dir, path);


    initscr();
    cbreak();
    noecho();

    int sizeX, sizeY = 0;
    int oldsizeX, oldsizeY = 0;
    getmaxyx(stdscr, sizeY, sizeX);

    MenuWindow filesWin(sizeY - 3, sizeX - 4, 1, 2);
    TerminalWindow terminalWin(sizeY - (sizeY - 2), sizeX - 4, sizeY - 2, 2);
    

    // WINDOW *filesWin = newwin(endY - 2, endX - 4, beginY + 1, beginX + 2);
    keypad(stdscr, true);
    box(filesWin.win, 0, 0);
    // mvwprintw(filesWin,2, 2, "Wau!");

    int input;
    while (true)
    {
        getmaxyx(stdscr, sizeY, sizeX);
        if (oldsizeX != sizeX || oldsizeY != sizeY)
        {
            filesWin.resize(sizeY - 3, sizeX - 4, 1, 2, true);
            terminalWin.resize(terminalWin.sizeY, sizeX - 4,sizeY - 2, 2, false);
        }

        filesWin.printMenu(Dir);
        mvprintw(0, 2, PathToString(path).c_str());
        refresh();

        // input
        wrefresh(terminalWin.win);
        wrefresh(filesWin.win);
        input = getch();

        if (terminalWin.TerminalMode)
            terminalWin.input(input, PathToString(path));

        if (!terminalWin.TerminalMode)
        {
            erase();
            filesWin.input(input, Dir.size(), Dir, path);
            if (input == 58)
            {
                terminalWin.TerminalMode = true;
                terminalWin.command = "";
                mvwprintw(terminalWin.win,0, 0, ":");
            }
        }

        //
        oldsizeX = sizeX;
        oldsizeY = sizeY;

    }

    refresh();
    getch();

    endwin();

    return 0;
}
