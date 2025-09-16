#include "game_logic.h"
#include "ui.h"
#include <stdlib.h>

#define ENEMY_SPAWN_DELAY 4
void spawn_enemy(Enemy enemies[], int max_enemies, int game_width){
    for (int i = 0; i < max_enemies; ++i){
        if (!enemies[i].active){
            enemies[i].active = 1;
            enemies[i].x = rand() % (GAME_WIDTH - 2) + 1;
            enemies[i].y = 1;
            enemies[i].dy = 1;
            enemies[i].character = 'V';
            enemies[i].health = 1;
            break; 
        }   
    }
}

void player_shoot(Bullet bullets[], int max_bullets, int px, int py){
    for (int i = 0; i < max_bullets; ++i){
        if (!bullets[i].active){
            bullets[i].active = 1;
            bullets[i].x = px;
            bullets[i].y = py - 1;
            bullets[i].dy = -1;
            bullets[i].character = '|';
            break;
        }
    }
}

void update_bullets(Bullet bullets[], int max_bullets){
    for (int i = 0; i < max_bullets; ++i){
        if (bullets[i].active){
            bullets[i].y += bullets[i].dy; 
            if (bullets[i].y < 1){
                bullets[i].active = 0;
            }
        }

    }

}

void update_enemies(Enemy enemies[], int max_enemies, int game_height, int game_timer, int speed_divider){
    if (game_timer < ENEMY_SPAWN_DELAY){
        return;
    }

    if (game_timer % speed_divider == 0 && speed_divider > 0){
        for (int i = 0; i < max_enemies; ++i){
            if (enemies[i].active){
                enemies[i].y += enemies[i].dy;
            
                if (enemies[i].y > game_height - 2){
                    enemies[i].active = 0;
                } 
            }    
        }   
    }
}

void handle_collisions(Bullet bullets[], int max_bullets, Enemy enemies[], int max_enemies, int* score){
    for (int i = 0; i < max_bullets; ++i){
        if (bullets[i].active){
            for (int j = 0; j < max_enemies; ++j){
                if (enemies[j].active){
                    if (bullets[i].x == enemies[j].x && (bullets[i].y == enemies[j].y || bullets[i].y + 1 == enemies[j].y)){

                        bullets[i].active = 0;
                        enemies[j].active = 0;

                        (*score)++;
                        break;
                    }
                }
            }
        }
    }
}

int check_player_collision(const Player* p, const Enemy enemies[], int max_enemies){
        for (int i = 0; i < max_enemies; ++i){
            if (enemies[i].active) {
                if (p->x == enemies[i].x && p->y == enemies[i].y){
                    return 1;
            }
        }
    }
    return 0;
}


void spawn_meteor(Meteor meteors[], int max_meteors){
    for (int i = 0; i < max_meteors; i++){
        if (!meteors[i].active){
            meteors[i].active = 1;
            meteors[i].x = (rand() % (GAME_WIDTH - 7)) + 3;
            meteors[i].y = 1;
            break;
        }
    }
}
void update_meteors(Meteor meteors[], int max_meteors, int game_timer, int speed_divider) {
    if (speed_divider > 0 && game_timer % (speed_divider * 2) == 0) {
        for (int i = 0; i < max_meteors; i++) {
            if (meteors[i].active) {
                meteors[i].y++; 

                if (meteors[i].y > GAME_HEIGHT - 2) {
                    meteors[i].active = 0;
                }
            }
        }
    }
}

int check_meteor_collision(const Player* p, const Meteor meteors[], int max_meteors) {
    for (int i = 0; i < max_meteors; i++) {
        if (meteors[i].active) {
            if (p->y == meteors[i].y && abs(p->x - meteors[i].x) <= 2) {
                return 1; 
            }
        }
    }
    return 0; 
}

void handle_bullet_meteor_collisions(Bullet bullets[], int max_bullets, Meteor meteors[], int max_meteors) {
    for (int i = 0; i < max_bullets; i++) {
        if (bullets[i].active) {
            for (int j = 0; j < max_meteors; j++) {
                if (meteors[j].active) {
                    if (abs(bullets[i].x - meteors[j].x) <= 2 &&
                       (bullets[i].y == meteors[j].y || bullets[i].y + 1 == meteors[j].y))
                    {
                        bullets[i].active = 0; 

                        break;
                    }
                }
            }
        }
    }
}
