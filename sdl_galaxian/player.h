#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdbool.h>

// GALIXIP (PLAYER SHIP)

#define PLAYER_Y 220
#define PLAYER_SIZE_X 13
#define PLAYER_SIZE_Y 16

typedef struct player_s {
    int x;
} Player;

// PLAYER MISSILE

#define MISSILE_SIZE_X 1
#define MISSILE_SIZE_Y 4
#define MISSILE_SPEED_Y -4
#define MISSILE_OFFSET_FROM_PLAYER_X 6
#define MISSILE_OFFSET_FROM_PLAYER_Y -4

typedef struct missile_s {
    bool fired;
    int x;
    int y;
} Missile;

void player_render(Player *player);
void player_move(Player *player, int dir);

void missile_render(Missile *missile, Player *player);
void missile_shoot(Missile *missile, Player *player);

#endif /* PLAYER_H_ */
