#ifndef ALIENS_H_
#define ALIENS_H_

#include <stdbool.h>
#include "player.h"

// ALIENS FORMATION
//
//                    01       01                       ; flagships
//                 01 01 01 01 01 01                    ; red
//              01 01 01 01 01 01 01 01                 ; purple
//           01 01 01 01 01 01 01 01 01 01              ; blue
//           01 01 01 01 01 01 01 01 01 01              ; blue
//           01 01 01 01 01 01 01 01 01 01              ; blue

#define FORMATION_DIM_Y 10
#define FORMATION_DIM_X 10
#define ALIEN_SIZE_X 16
#define ALIEN_SIZE_Y 16
#define FORMATION_Y 10
#define ALIEN_OFFSET_X 15
#define ALIEN_OFFSET_Y 12
#define NUM_EXPLOSION_FRAMES 4

typedef enum {
    RED = 0,
    PURPLE = 1,
    BLUE = 2,
    YELLOW = 3
} Color;

typedef struct formationAlien_s {
    bool isActive;
    bool isDying;
    int explosionFrame;
} FormationAlien;

typedef struct formation_s {
    FormationAlien alien[FORMATION_DIM_Y][FORMATION_DIM_X];
    enum {
        LEFT = 0,
        RIGHT = 1
    } dir;
    int offset_x;
} Formation;

// INFLIGHT ALIEN
//

typedef struct inflightAlien_s {
    bool isActive;
    bool isDying;
    int stageOfLife;
    int x;
    int y;
    int animationFrame;
    bool arcClockwise;
    int indexInFormation;
    int pivotYValue;
    // ...
    int sortieCount;
    int speed;

} InflightAlien;

// SHELLS (ALIEN MISSILES)

// ...

void formation_init(Formation *formation);
void formation_render(Formation *formation);

void formation_detect_missile_collision(Formation *formation, Missile *missile);

#endif /* ALIENS_H_ */
