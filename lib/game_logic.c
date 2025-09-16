#include "game_logic.h"
#include "ui.h"
#include <stdlib.h>

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

void player_shoot(Bullet bullets[], int max_bullets, const Player* p){
    for (int i = 0; i < max_bullets; ++i){
        if (!bullets[i].active){
            bullets[i].active = 1;
            bullets[i].x = p->x;
            bullets[i].y = p->y - 1;
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

void update_enemies(Enemy enemies[], int max_enemies, int game_height){
    for (int i = 0; i < max_enemies; ++i){
        if (enemies[i].active){
            enemies[i].y += enemies[i].dy;
            
            if (enemies[i].y > game_height - 2){
                enemies[i].active = 0;
            } 
        }    
    }
}

void handle_collisions(Bullet bullets[], int max_bullets, Enemy enemies[], int max_enemies, int* score){
    for (int i = 0; i < max_bullets; ++i){
        if (bullets[i].active){
            for (int j = 0; j < max_enemies; ++j){
                if (enemies[j].active){
                    if (bullets[i].x == enemies[j].x && bullets[i].y == enemies[j].y){

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




