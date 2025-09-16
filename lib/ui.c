#include "ui.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>



static int screen_height;
static int screen_width;

void ui_init() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    set_escdelay(25);
    getmaxyx(stdscr, screen_height, screen_width);

    start_color();
    init_pair(PLAYER_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK); 
    init_pair(TRAIL_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);
}

void ui_cleanup(WINDOW *win) {
    delwin(win);
    endwin();
}

WINDOW* create_game_window() {
    if (screen_height < GAME_HEIGHT || screen_width < GAME_WIDTH) {
        endwin();
        printf("Terminal too small. Please resize to at least %d x %d\n", GAME_WIDTH, GAME_HEIGHT);
        exit(1);
    }
    
    int start_y = (screen_height - GAME_HEIGHT) / 2;
    int start_x = (screen_width - GAME_WIDTH) / 2;
    
    WINDOW *game_win = newwin(GAME_HEIGHT, GAME_WIDTH, start_y, start_x);
    keypad(game_win, TRUE);
    nodelay(game_win, TRUE);
    
    return game_win;
}

void handle_resize(WINDOW **win_ptr) {
    delwin(*win_ptr);
    clear();
    
    getmaxyx(stdscr, screen_height, screen_width);

    while (screen_height < GAME_HEIGHT || screen_width < GAME_WIDTH) {
        mvprintw(0, 0, "Terminal is too small!");
        mvprintw(1, 0, "Please resize to at least %d x %d to continue.", GAME_WIDTH, GAME_HEIGHT);
        refresh();
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, screen_height, screen_width);
            clear();
        }
    }

    int start_y = (screen_height - GAME_HEIGHT) / 2;
    int start_x = (screen_width - GAME_WIDTH) / 2;
    *win_ptr = newwin(GAME_HEIGHT, GAME_WIDTH, start_y, start_x);
    
    keypad(*win_ptr, TRUE);
    nodelay(*win_ptr, TRUE);
    
    refresh();
}

int get_screen_height() { return screen_height; }
int get_screen_width() { return screen_width; }
