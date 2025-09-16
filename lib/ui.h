#ifndef UI_H
#define UI_H

#include <ncurses.h>

#define GAME_HEIGHT 20
#define GAME_WIDTH 20
#define PLAYER_COLOR_PAIR 1 
#define TRAIL_COLOR_PAIR 2
void ui_init();

void ui_cleanup(WINDOW *win);

WINDOW* create_game_window();

void handle_resize(WINDOW **win_ptr);

int get_screen_height();
int get_screen_width();

#endif 
