//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <emscripten.h>
#include "render.h"
#include "player.h"
#include "aliens.h"
#include "stars.h"

SDL_Surface *surface;

// entit y
// common
// game
// input
// render / draw
// resources
// sound

Player player;
Missile missile;
Formation formation;
Stars stars;

void mainLoop()
{
    /*if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    Uint8 *pixels = surface->pixels;

    int pixelCount = SCREEN_WIDTH * SCREEN_HEIGHT;
    int byteCount = pixelCount * 4;

    for (int i = 0; i < byteCount; i++) {
        char randomByte = rand() % 50;
        pixels[i] = randomByte;
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderClear(renderer);
    renderCopyScaled(renderer, screenTexture, NULL, NULL);*/

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT]) {
        player_move(&player, -1);
    }

    if (state[SDL_SCANCODE_RIGHT]) {
        player_move(&player, +1);
    }

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            if (state[SDL_SCANCODE_SPACE]) {
                missile_shoot(&missile, &player);
            }
            break;

        case SDL_KEYUP:
            break;

        default:
            break;
        }
    }

    SDL_RenderClear(renderer);

    // Initialize global vars
    /*
    memset(&player, 0, sizeof player);
    memset(&missile, 0, sizeof missile);
    memset(&formation, 0, sizeof formation);
    memset(&stars, 0, sizeof stars);
    */

    formation_detect_missile_collision(&formation, &missile);

    stars_render(&stars);
    formation_render(&formation);
    player_render(&player);
    missile_render(&missile, &player);

    /*
    SDL_Rect windowOrigRect = { 1, 1, 16, 16 };
    SDL_Rect windowDestRect = { 1, 1, 16, 16 };

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {

            windowOrigRect.y = 1 + (i % 4) * 17;
            windowOrigRect.x = 1 + (j % 7) * 17;

            windowDestRect.x = 10 + j * 15;
            windowDestRect.y = 10 + i * 15;
            renderCopyScaled(renderer, everythingTexture, &windowOrigRect, &windowDestRect);
        }
    }
    */

    SDL_RenderPresent(renderer);

    // SDL_DestroyTexture(screenTexture);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    render_init();

    stars_init(&stars);
    formation_init(&formation);

    // surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

    emscripten_set_main_loop(mainLoop, 60, 0);
}
