#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <ncurses.h>

typedef struct {

    int x;
    int y;
    int base_speed_divider;
    char character;
    attr_t attribute;

} Star;

void init_starfield(Star starfield[], int max_stars);

void update_starfield(Star starfield[], int max_stars, int game_timer, int score);

#endif
