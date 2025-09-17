#include "background.h"
#include "ui.h"
#include <stdlib.h>

void init_starfield(Star starfield[], int max_stars){

    for (int i=0; i<max_stars; i++){
        starfield[i].x = rand() % (GAME_WIDTH - 2) + 1;
        starfield[i].y = rand() % (GAME_HEIGHT - 2) + 1;
        int chance = rand() % 100;

        if (chance < 8){
            starfield[i].base_speed_divider = 6;
            starfield[i].character = '.';
            starfield[i].attribute = A_BOLD;
        } else if (chance < 28){
            starfield[i].base_speed_divider = 8;
            starfield[i].character = '|';
            starfield[i].attribute = A_NORMAL;
        } else {
            starfield[i].base_speed_divider = 12;
            starfield[i].character = '.';
            starfield[i].attribute = A_DIM;
        }
    }
}
void update_starfield(Star starfield[], int max_stars, int game_timer, int score){

    for (int i = 0; i< max_stars; i++){

        int current_divider = starfield[i].base_speed_divider - (score / 5);

        if (current_divider < 1) {
            current_divider = 1;

        }



        if (game_timer % current_divider == 0){
            starfield[i].y++;
        }

        if (starfield[i].y >= GAME_HEIGHT - 1){
            starfield[i].y = 1;
            starfield[i].x = rand() % (GAME_WIDTH - 2) + 1;
        }
    }

}
