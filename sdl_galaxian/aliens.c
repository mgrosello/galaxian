#include <emscripten.h>
#include "render.h"
#include "aliens.h"
#include "player.h"

void formation_init(Formation *formation)
{
    for (int i = 0; i < FORMATION_DIM_Y; i++) { // ROW

        // Reset columns
        for (int j = 0; j < FORMATION_DIM_X; j++)
            formation->alien[i][j].isActive = false;

        // Flagships row
        if (i == 0) {
            formation->alien[i][3].isActive = true;
            formation->alien[i][6].isActive = true;

            // Other rows
        } else {
            for (int j = 0; j < FORMATION_DIM_X; j++) {
                if ((i == 1 && j >= 2 && j < 8) || // red row
                    (i == 2 && j >= 1 && j < 9) || // purple row
                    i > 2) { // blue rows
                    formation->alien[i][j].isActive = true;
                }
            }
        }
    }
}

void formation_render(Formation *formation)
{
    static int tick = 0;
    static int frame_counter = 0;

    for (int i = 0; i < FORMATION_DIM_Y; i++) {
        for (int j = 0; j < FORMATION_DIM_X; j++) {

            FormationAlien *alien = &formation->alien[i][j];
            if (alien->isActive) {

                Color color = BLUE; // default
                if (i == 0)
                    color = YELLOW;
                else if (i == 1)
                    color = RED;
                else if (i == 2)
                    color = PURPLE;

                int frame = 0;
                SDL_Rect windowSpriteRect;
                if (alien->isDying) {
                    SDL_Rect explosionSpriteRect = { 61 + (ALIEN_SIZE_X + 1) * alien->explosionFrame, 70, ALIEN_SIZE_X, ALIEN_SIZE_Y };
                    windowSpriteRect = explosionSpriteRect;
                    if (tick % 4 == 0) {
                        alien->explosionFrame++;
                        if (alien->explosionFrame >= NUM_EXPLOSION_FRAMES) {
                            alien->isActive = false;
                        }
                    }
                } else {
                    // TODO: animation is not arcade exact by any means
                    if (i > 0) { // No frame animation for yellow
                        frame = (frame_counter / 16 + j) % 2;
                    }
                    SDL_Rect alienSpriteRect = { 1 + (ALIEN_SIZE_X + 1) * frame, 1 + color * (ALIEN_SIZE_Y + 1), ALIEN_SIZE_X, ALIEN_SIZE_Y };
                    windowSpriteRect = alienSpriteRect;
                }
                SDL_Rect windowDestRect = { formation->offset_x + ALIEN_OFFSET_X * j - frame * 2, FORMATION_Y + ALIEN_OFFSET_Y * i, ALIEN_SIZE_X, ALIEN_SIZE_Y };
                renderCopyScaled(renderer, everythingTexture, &windowSpriteRect, &windowDestRect);
            }
        }
    }
    const int max_offset_x = SCREEN_WIDTH - FORMATION_DIM_X * ALIEN_OFFSET_X;
    if (tick++ % 3 == 0) {
        if (formation->offset_x <= 0)
            formation->dir = RIGHT;
        else if (formation->offset_x > max_offset_x)
            formation->dir = LEFT;
        formation->dir == LEFT ? formation->offset_x-- : formation->offset_x++;
        frame_counter++;
    }
}

void formation_detect_missile_collision(Formation *formation, Missile *missile)
{
    if (!missile->fired)
        return;
    SDL_Rect missileRect = { missile->x, missile->y, MISSILE_SIZE_X, MISSILE_SIZE_Y };
    for (int i = 0; i < FORMATION_DIM_Y; i++) {
        for (int j = 0; j < FORMATION_DIM_X; j++) {
            FormationAlien *alien = &formation->alien[i][j];
            if (alien->isActive) {
                SDL_Rect alienRect = { formation->offset_x + ALIEN_OFFSET_X * j, FORMATION_Y + ALIEN_OFFSET_Y * i, ALIEN_SIZE_X, ALIEN_SIZE_Y };
                if (SDL_HasIntersection(&alienRect, &missileRect)) {
                    alien->isDying = true;
                    alien->explosionFrame = 0;
                    missile->fired = false;
                    return;
                }
            }
        }
    }
}
