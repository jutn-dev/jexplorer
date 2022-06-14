#include <iostream>
#include <ncurses.h>
#include <filesystem>

int main()
{
    //     std::string path = "/home/juho/couding";
    // for (const auto & entry : std::filesystem::directory_iterator(path))
    //     std::cout << entry.path() << std::endl;
    // if(system("konsole -e nvim") != 0)
    //     std::cout << " no terminal \n";

    // int b = 1;
    initscr();
    cbreak();
    noecho();

    int beginX, beginY, endX, endY;
    getbegyx(stdscr, beginY, beginX);
    getmaxyx(stdscr, endY, endX);

    WINDOW* filesWin = newwin(endY - 2, endX - 4, beginY + 1 ,beginX + 2);
    keypad(filesWin, true);
    box(filesWin,0,0);
    //mvwprintw(filesWin,2, 2, "Wau!");

    std::string files[] = {"ok","wau","idk"};
    int kohdalla = 0;
    int choice;
    while (true)
    {
        for (int i = 0; i < 3; i++)
        {
            if(i == kohdalla)
                wattron(filesWin, A_REVERSE);
            mvwprintw(filesWin,i+1,1,files[i].c_str());
            wattroff(filesWin, A_REVERSE);
        }
        choice = wgetch(filesWin);

        switch (choice)
        {
        case KEY_UP:
            kohdalla--;
            break;
        
        case KEY_DOWN:
            kohdalla++;
        
        default:
            break;
        }
        if(kohdalla < 0)
            kohdalla = 0;
        if(kohdalla > 2)
            kohdalla = 2;
        
    }
    

    refresh();
    wrefresh(filesWin);
    getch();


    endwin();

    return 0;
}



//
//