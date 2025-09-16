#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "enemy.h"
#include "game_logic.h"
#include "bullet.h"
#include "ui.h"
#include "player.h"

#define MAX_BULLETS 50
#define MAX_ENEMIES 20
#define SHOOT_COOLDOWN 8

int main() {

    srand(time(NULL) ^ getpid());
    ui_init();

    int last_shot_time =0;
    int yMax, xMax;
    WINDOW *game_win = create_game_window(&yMax, &xMax);

    Player p = {GAME_WIDTH / 2, GAME_HEIGHT - 2, 'M'};
    Enemy enemies[MAX_ENEMIES] = {0};
    Bullet bullets[MAX_BULLETS] = {0};

    int score = 0;
    int game_timer = 0;

    int ch;

    while ((ch = wgetch(game_win)) != 'q') {
        
        if (ch == KEY_RESIZE) {
            handle_resize(&game_win, &yMax, &xMax);
            continue;
        }
        
        if (ch != ERR) {
            switch (ch) {
                case 'a': if (p.x > 1) p.x--; break;
                case 'd': if (p.x < GAME_WIDTH - 2) p.x++; break;
                case ' ': {
                    if (game_timer - last_shot_time > SHOOT_COOLDOWN){
                        player_shoot(bullets, MAX_BULLETS, &p);
                        last_shot_time = game_timer;
                    }
                    break;
                }
            }
        }

        if (game_timer % 30 == 0){
            spawn_enemy(enemies, MAX_ENEMIES, GAME_WIDTH);
        }
        update_bullets(bullets, MAX_BULLETS);
        update_enemies(enemies, MAX_BULLETS, GAME_HEIGHT);
        handle_collisions(bullets, MAX_BULLETS, enemies, MAX_ENEMIES, &score);


        werase(game_win);
        box(game_win, 0, 0);
        mvwprintw(game_win, p.y, p.x, "%c", p.character);
        
        for (int i = 0 ; i < MAX_BULLETS; ++i){
            if (bullets[i].active){
                mvwprintw(game_win, bullets[i].y, bullets[i].x, "%c", bullets[i].character);
            }
        }

        for (int i = 0; i < MAX_ENEMIES; ++i) {
            if (enemies[i].active) {
                mvwprintw(game_win, enemies[i].y, enemies[i].x, "%c", enemies[i].character);
            }
        }

        mvwprintw(game_win, 1, 2, "Score: %d", score);

        wrefresh(game_win);
        

        game_timer++;
        usleep(30000);

    }
    

    ui_cleanup(game_win);

    return 0;
}
