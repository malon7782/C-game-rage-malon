#ifndef UI_H
#define UI_H

#include <ncurses.h>

#define GAME_HEIGHT 20
#define GAME_WIDTH 30

void ui_init();

void ui_cleanup(WINDOW *win);

WINDOW* create_game_window(int* yMax, int* xMax);

void handle_resize(WINDOW **win_ptr, int* yMax, int* xMax);

#endif 
