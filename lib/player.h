#ifndef PLAYER_H
#define PLAYER_H
#define TRAIL_LENGTH 8
typedef struct {
    int x;
    int y;
} Coord;

typedef struct {
    int x;
    int y;
    int dx;
    char character;
    Coord trail[TRAIL_LENGTH];
    int trail_index;

} Player;


#endif
