#include <emscripten.h>
#include "render.h"
#include "player.h"

void player_render(Player *player)
{
    const SDL_Rect playerSpriteRect = { 3, 70, PLAYER_SIZE_X, PLAYER_SIZE_Y };
    SDL_Rect playerDestRect = { player->x, PLAYER_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y };

    renderCopyScaled(renderer, everythingTexture, &playerSpriteRect, &playerDestRect);
}

void player_move(Player *player, int dir)
{
    if (player->x > 0 && dir < 0)
        player->x += dir;
    if (player->x < SCREEN_WIDTH - PLAYER_SIZE_X && dir > 0)
        player->x += dir;
}

void missile_render(Missile *missile, Player *player)
{
    const SDL_Rect missileSpriteRect = { 66, 196, MISSILE_SIZE_X, MISSILE_SIZE_Y - 1 };
    int x, y;
    if (missile->fired) {
        x = missile->x;
        y = missile->y;
    } else {
        x = player->x + MISSILE_OFFSET_FROM_PLAYER_X;
        y = PLAYER_Y + MISSILE_OFFSET_FROM_PLAYER_Y;
    }
    SDL_Rect missileDestRect = { x, y, MISSILE_SIZE_X, MISSILE_SIZE_Y };
    if (missile->fired) {
        missile->y = missile->y + MISSILE_SPEED_Y;
        if (missile->y <= 0) {
            missile->fired = false;
        }
    }

    renderCopyScaled(renderer, everythingTexture, &missileSpriteRect, &missileDestRect);
}

void missile_shoot(Missile *missile, Player *player)
{
    if (!missile->fired) {
        missile->fired = true;
        missile->x = player->x + MISSILE_OFFSET_FROM_PLAYER_X;
        missile->y = PLAYER_Y + MISSILE_OFFSET_FROM_PLAYER_Y;
    }
}
