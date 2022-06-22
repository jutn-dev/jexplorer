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
    
    if (!has_colors())
    {
        std::cerr << "Your terminal doesnt have color \n";
        endwin();
        return -1;
    }
    start_color();
    use_default_colors();
    if(COLOR_PAIRS < 7)
    {
        std::cerr << "Your terminal has only 8 colors \n";
        endwin();
        return -1;
    }
    if (!can_change_color())
    {
        std::cerr << "Your terminal cannot change colors \n";
        endwin();
        return -2;
    }
    init_color(2, 127, 518, 430);
    init_pair(1, COLOR_WHITE, 2);
    // if (!has_colors_sp())
    // {
    //     std::cerr << "Your terminal doesnt have color";
    //     return -1;
    // }

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
            terminalWin.resize(terminalWin.sizeY, sizeX - 4, sizeY - 2, 2, false);
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
                mvwprintw(terminalWin.win, 0, 0, ":");
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
