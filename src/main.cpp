#include <iostream>
#include <ncurses.h>
#include <filesystem>
#include <vector>

#include "io.hpp"

// void bb(char b);

int main()
{
    //     std::string path = "/home/juho/couding";
    // for (const auto & entry : std::filesystem::directory_iterator(path))
    //     std::cout << entry.path() << std::endl;
    // if(system("konsole -e nvim") != 0)
    //     std::cout << " no terminal \n";
    // int b = 1;
    std::string path = "/";
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

    WINDOW *filesWin = newwin(endY - 2, endX - 4, beginY + 1, beginX + 2);
    keypad(filesWin, true);
    box(filesWin, 0, 0);
    // mvwprintw(filesWin,2, 2, "Wau!");

    int highlighted = 0;
    int choice;
    while (true)
    {
        getmaxyx(stdscr, endY, endX);

        if (oldendX != endX || oldendY != endY)
        {
            clear();
            wclear(filesWin);
            wresize(filesWin, endY - 2, endX - 4);
            box(filesWin, 0, 0);
            refresh();
            wrefresh(filesWin);
        }

        for (int i = 0; i < Dir.size(); i++)
        {
            if (i == highlighted)
                wattron(filesWin, A_REVERSE);
            mvwprintw(filesWin, i + 1, 1, "%s %s", Dir[i].fileType.c_str(), Dir[i].file.c_str());
            wattroff(filesWin, A_REVERSE);
        }
        choice = wgetch(filesWin);

        switch (choice)
        {
        case KEY_UP:
            highlighted--;
            break;

        case KEY_DOWN:
            highlighted++;

        default:
            break;
        }
        if (choice == 10)
        {
            if (std::filesystem::directory_entry(path + Dir[highlighted].file).is_directory())
            {
                path += Dir[highlighted].file + "/";
                LoadDir(Dir, path);
                wclear(filesWin);
            }
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
    wrefresh(filesWin);
    getch();

    endwin();

    return 0;
}
