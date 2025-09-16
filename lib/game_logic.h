#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "meteor.h"

void spawn_enemy(Enemy enemies[], int max_enemies, int game_width);
void spawn_meteor(Meteor meteors[], int max_meteors);
void player_shoot(Bullet bullets[], int max_bullets, int px, int py);
void update_bullets(Bullet bullets[], int max_bullets);
void handle_collisions(Bullet bullets[], int max_bullets, Enemy enemies[], int max_enemies, int* score);
void update_enemies(Enemy enemies[], int max_enemies, int game_width, int game_timer, int speed_divider);
void update_meteors(Meteor meteors[], int max_meteors, int game_timer, int speed_divider);
int check_player_collision(const Player* p, const Enemy enemies[], int max_enemies);
int check_meteor_collision(const Player* p, const Meteor meteors[], int max_meteors);
void handle_bullet_meteor_collisions(Bullet bullets[], int max_bullets, Meteor meteors[], int max_meteors);
#endif
