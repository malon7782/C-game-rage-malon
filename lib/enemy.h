#ifndef ENEMY_H
#define ENEMY_H

typedef enum {
    BASIC,
    SHOOTER,
    WAVY
} EnemyType;

typedef struct {
    int x, y;
    int dx, dy;
    char character;
    int active;
    EnemyType type;
    int health;
} Enemy;

#endif
