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
    // std::string b = runCommand("cat cdawwdadwaa", PathToString(path));
    path.push_back("/");

    if (argc > 1)
    {
        StringToPath(argv[1], path);
    }

    std::vector<Directory> Dir;
    LoadDir(Dir, path);
    // init("bbb");
    // loadDir(3);

    bool TerminalMode = false;
    std::string command;

    initscr();
    cbreak();
    noecho();

    int beginX, beginY, endX, endY = 0;
    int oldbeginX, oldbeginY, oldendX, oldendY = 0;
    getbegyx(stdscr, beginY, beginX);
    getmaxyx(stdscr, endY, endX);

    window filesWin(endY - 3, endX - 4, beginY + 1, beginX + 2);
    // TerminalWindow winn(endY - 1, endX - 2, endY - 2, endX - 2);
    

    // WINDOW *filesWin = newwin(endY - 2, endX - 4, beginY + 1, beginX + 2);
    keypad(filesWin.win, true);
    box(filesWin.win, 0, 0);
    // mvwprintw(filesWin,2, 2, "Wau!");

    int choice;
    while (true)
    {
        getmaxyx(stdscr, endY, endX);
        if (oldendX != endX || oldendY != endY)
        {
            filesWin.resize(endY - 3, endX - 4, true);
        }

        filesWin.printMenu(Dir);
        mvprintw(0, 2, PathToString(path).c_str());
        refresh();

        // input
        choice = wgetch(filesWin.win);

        if (TerminalMode)
        {
            if (choice == 10)
            {
                std::string result = runCommand(command, PathToString(path));
                move(endY - 1, 0);
                if (result == "")
                    printw("Error: command failed to execute");
                else
                {
                    printw("%s", result.c_str());
                }
            }
            else
            {
                command += (char)choice;
                mvprintw(endY - 2, 1, "%s", command.c_str());
            }
            if (choice == 27) // 27 == esc
            {
                TerminalMode = false;
                clear();
                refresh();
            }
        }

        if (!TerminalMode)
        {
            erase();
            filesWin.input(choice, Dir.size(), Dir, path);
            if (choice == 58)
            {
                TerminalMode = true;
                command = "";
                mvprintw(endY - 2, 0, ":");
            }
        }

        //
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
