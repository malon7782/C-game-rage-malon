#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "enemy.h"
#include "game_logic.h"
#include "bullet.h"
#include "ui.h"
#include "player.h"
#include "meteor.h"

#define MAX_BULLETS 50
#define MAX_ENEMIES 100
#define SHOOT_COOLDOWN 20
#define PLAYER_SPEED_DIVIDER 3
#define MAX_METEORS 20

int main() {

    srand(time(NULL) ^ getpid());
    ui_init();

    int last_shot_time =0;
    WINDOW *game_win = create_game_window();

    Player p = {GAME_WIDTH / 2, GAME_HEIGHT - 2, 0, 'M'};
    p.trail_index = 0;
    for (int i = 0; i < TRAIL_LENGTH; i++){
        p.trail[i].x = p.x;
        p.trail[i].y = p.y;

    }

    
    Enemy enemies[MAX_ENEMIES] = {0};
    Bullet bullets[MAX_BULLETS] = {0};
    Meteor meteors[MAX_METEORS] = {0};

    int score = 0;
    int game_timer = 0;

    int initial_enemy_speed_divider = 10;
    int initial_spawn_interval = 50;
    
    int game_over = 0;
    int ch;

    while (!game_over && (ch = wgetch(game_win)) != 'q') {
        
        if (ch == KEY_RESIZE) {
            handle_resize(&game_win);
            continue;
        }
        
        if (ch != ERR) {
            switch (ch) {
                case 'a': p.dx = -1; break;
                case 'd': p.dx = 1; break;
                case ' ': {
                    if (game_timer - last_shot_time > SHOOT_COOLDOWN){
                        player_shoot(bullets, MAX_BULLETS, p.x, p.y);
                        last_shot_time = game_timer;
                    }
                    break;
                }
            }
        }

        int enemy_speed_divider = initial_enemy_speed_divider - ( score / 3 );

        if (enemy_speed_divider < 2) { enemy_speed_divider = 2;}

        int spawn_interval = initial_spawn_interval - (score / 6);

        if (spawn_interval < 5) {spawn_interval = 5;}




        if (game_timer % PLAYER_SPEED_DIVIDER == 0){
            p.x += p.dx;
  
        }
       

        if (p.x < 1) p.x = 1;
        if (p.x > GAME_WIDTH - 2) p.x = GAME_WIDTH - 2;

        if (game_timer % spawn_interval == 0){
            spawn_enemy(enemies, MAX_ENEMIES, GAME_WIDTH);
        }

        if (game_timer % (spawn_interval * 8) == 0 && score >= 8){
            spawn_meteor(meteors, MAX_METEORS);
        }

        update_bullets(bullets, MAX_BULLETS);
        update_enemies(enemies, MAX_ENEMIES, GAME_HEIGHT, game_timer, enemy_speed_divider);
        update_meteors(meteors, MAX_METEORS, game_timer, enemy_speed_divider);

        handle_collisions(bullets, MAX_BULLETS, enemies, MAX_ENEMIES, &score);
        handle_bullet_meteor_collisions(bullets, MAX_BULLETS, meteors, MAX_METEORS);


        werase(game_win);
        box(game_win, 0, 0);

        wattron(game_win, A_DIM | COLOR_PAIR(TRAIL_COLOR_PAIR));
        for (int i = 0; i < TRAIL_LENGTH; i++) {
            if (i == p.trail_index && (rand() % 3 ==0)) continue;
             mvwprintw(game_win, p.trail[i].y, p.trail[i].x, "%c", p.character);
        }
        wattroff(game_win, A_DIM | COLOR_PAIR(TRAIL_COLOR_PAIR));


        wattron(game_win, COLOR_PAIR(PLAYER_COLOR_PAIR));
        mvwprintw(game_win, p.y, p.x, "%c", p.character);
        wattroff(game_win, COLOR_PAIR(PLAYER_COLOR_PAIR));
        
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
    
        for (int i = 0; i < MAX_METEORS; ++i){
            if (meteors[i].active){
                mvwprintw(game_win, meteors[i].y, meteors[i].x - 1, "*****");  
            }
        }

        mvwprintw(game_win, 1, 2, "Score: %d", score);

        if (check_player_collision(&p, enemies, MAX_ENEMIES) || check_meteor_collision(&p, meteors, MAX_METEORS)){
            game_over = 1;
        }



        wrefresh(game_win);
        p.trail[p.trail_index].x = p.x;
        p.trail[p.trail_index].y = p.y;
        p.trail_index = (p.trail_index + 1) % TRAIL_LENGTH;

        game_timer++;
        usleep(15000);

    }
    mvwprintw(game_win, GAME_HEIGHT / 2, (GAME_WIDTH / 2) - 5, "GAME OVER");
    mvwprintw(game_win, GAME_HEIGHT / 2 + 1, (GAME_WIDTH / 2) - 8, "Press 'q' to exit");

    wrefresh(game_win);
    nodelay(game_win, FALSE);

    while(wgetch(game_win) != 'q');
    ui_cleanup(game_win);

    return 0;
}
    

  
