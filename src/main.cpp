#include <iostream>
#include <ncurses.h>
#include <filesystem>
#include <vector>
#include <array>

#include "io.hpp"
#include "windows.hpp"


std::vector<std::array<std::string,2>> open_file_using;


void initColors()
{
    if (!has_colors())
    {
        std::cerr << "Your terminal doesnt have color \n";
        endwin();
        exit(-1);
    }
    start_color();
    if (!can_change_color())
    {
        std::cerr << "Your terminal cannot change colors \n";
        endwin();
        exit(-1);
    }
    if (COLOR_PAIRS < 7)
    {
        std::cerr << "Your terminal has only 8 colors \n";
        endwin();
        exit(-1);
    }
    use_default_colors();
}

int main(int argc, char *argv[])
{
    LoadConfig();
    // std::string homePath = getenv("HOME");
    std::vector<std::string> path;
    path.push_back("/");

    if (argc > 1)
    {
        StringToPath(argv[1], path);
    }

    std::vector<File> Dir;
    LoadDir(Dir, path);

    initscr();
    clear();
    cbreak();
    noecho();


    initColors();
    //use_default_colors();
    init_color(3, 127, 518, 430);
    init_pair(1, COLOR_WHITE, 3);

    int sizeX, sizeY, oldsizeX, oldsizeY = 0;
    getmaxyx(stdscr, sizeY, sizeX);
    
    MenuWindow filesWin(sizeY - 3, sizeX - 4, 1, 2);
    TerminalWindow terminalWin(sizeY - (sizeY - 2), sizeX - 4, sizeY - 2, 2);
    TextWindow pathWin(PathToString(path), 1, sizeX - 2, 0, 2);
    // WINDOW *filesWin = newwin(endY - 2, endX - 4, beginY + 1, beginX + 2);
    keypad(pathWin.win, true);
    box(filesWin.win, 0, 0);
    // mvwprintw(filesWin,2, 2, "Wau!");

    int input;
    while (true)
    {
        getmaxyx(stdscr, sizeY, sizeX);
        
        //resize all windows
        if (oldsizeX != sizeX || oldsizeY != sizeY)
        {
            filesWin.resize(sizeY - 3, sizeX - 4, 1, 2, true);
            terminalWin.resize(terminalWin.sizeY, sizeX - 4, sizeY - 2, 2, false);
            pathWin.resize(1, sizeX - 2, 0, 2, false);
        }

        filesWin.printMenu(Dir);
        pathWin.setText(PathToString(path).c_str());        

        wrefresh(terminalWin.win);
        wrefresh(filesWin.win);
        //input / update
        input = wgetch(pathWin.win);

        if (terminalWin.TerminalMode)
            terminalWin.input(input, PathToString(path));

        if (!terminalWin.TerminalMode)
        {
            filesWin.input(input, Dir.size(), Dir, path);
            if (input == 58)
            {
                terminalWin.TerminalMode = true;
                terminalWin.command = "";
                mvwprintw(terminalWin.win, 0, 0, ":");
            }
        }

        oldsizeX = sizeX;
        oldsizeY = sizeY;
    }

    refresh();
    getch();

    endwin();

    return 0;
}
