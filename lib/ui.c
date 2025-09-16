#include "ui.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

void ui_init(){

    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    set_escdelay(25);
}

void ui_cleanup(WINDOW *win){

    delwin(win);
    endwin();

}

WINDOW* create_game_window(int* yMax_ptr, int* xMax_ptr){

    int y, x;
    getmaxyx(stdscr, y, x);
    *yMax_ptr = y;
    *xMax_ptr = x;

    if (*yMax_ptr < GAME_HEIGHT || *xMax_ptr < GAME_WIDTH){
    
        endwin();
        printf("Terminal too small. Please resize to at least %d * %d\n", GAME_WIDTH, GAME_HEIGHT);
        exit(1);

    }

    int start_y = (*yMax_ptr - GAME_HEIGHT) / 2;
    int start_x = (*xMax_ptr - GAME_WIDTH) / 2;

    WINDOW *game_win = newwin(GAME_HEIGHT, GAME_WIDTH, start_y, start_x);
    keypad(game_win, TRUE);
    nodelay(game_win, TRUE);
    return game_win;

}

void handle_resize(WINDOW **win_ptr, int* yMax_ptr, int* xMax_ptr) {
    delwin(*win_ptr);
    clear();
    int y, x;
    getmaxyx(stdscr, y, x);
    *yMax_ptr = y;
    *xMax_ptr = x;

    while (*yMax_ptr < GAME_HEIGHT || *xMax_ptr < GAME_WIDTH){
        mvprintw(0, 0, "Terminal is too small");
        mvprintw(1, 0, "Please resize to at least %d * %d to continue.", GAME_WIDTH, GAME_HEIGHT);
        refresh();

        int ch = getch();
        if (ch == KEY_RESIZE){
            getmaxyx(stdscr, y, x);
            *yMax_ptr = y;
            *xMax_ptr = x;
            clear();
        }
    }

    int start_y = (*yMax_ptr - GAME_HEIGHT) / 2;
    int start_x = (*xMax_ptr - GAME_WIDTH) / 2;

    *win_ptr = newwin(GAME_HEIGHT, GAME_WIDTH, start_y, start_x);

    keypad(*win_ptr, TRUE);
    nodelay(*win_ptr, TRUE);

    refresh();


}
