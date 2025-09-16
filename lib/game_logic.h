#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "player.h"
#include "bullet.h"
#include "enemy.h"

void spawn_enemy(Enemy enemies[], int max_enemies, int game_width);
void player_shoot(Bullet bullets[], int max_bullets, const Player *p);
void update_bullets(Bullet bullets[], int max_bullets);
void update_enemies(Enemy enemies[], int max_enemies, int game_width);
void handle_collisions(Bullet bullets[], int max_bullets, Enemy enemies[], int max_enemies, int* score);

#endif
