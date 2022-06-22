#include <iostream>
#include <ncurses.h>

#include "windows.hpp"

TextWindow::TextWindow(std::string p_Text, int p_sizeY, int p_sizeX, int p_posY, int p_posX)
    : window(p_sizeY, p_sizeX, p_posY, p_posX), Text(p_Text) {}

void TextWindow::setText(std::string p_Text)
{
    Text = p_Text;
    werase(win);
    mvwprintw(win, 0, 0, Text.c_str());
    wrefresh(win);
}
