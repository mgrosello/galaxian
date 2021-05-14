#include <emscripten.h>
#include "render.h"
#include "stars.h"

#define rgb(r, g, b) (r << 16 | g << 8 | b)
#define BIT(x, n) (((x) >> (n)) & 1)

void stars_render(Stars *stars)
{
    static int tick = 0;

    if (tick++ % 2 == 0) {

        if (SDL_MUSTLOCK(starsSurface))
            SDL_LockSurface(starsSurface);

        Uint32 *pixels = starsSurface->pixels;

        for (int i = 0; i < STAR_COUNT; i++) {
            Star *star = &stars->stars[i];
            int enabled = star->y & 0x8;
            pixels[star->y * SCREEN_WIDTH + star->x] = 0;
            if (star->y >= SCREEN_HEIGHT)
                star->y = 0;
            else
                star->y++;
            pixels[star->y * SCREEN_WIDTH + star->x] = enabled ? stars->star_color[star->color] : 0;
            // star->color = (star->color + 1) % 0x3f;
        }

        if (SDL_MUSTLOCK(starsSurface))
            SDL_UnlockSurface(starsSurface);
    }

    SDL_Texture *starsTexture = SDL_CreateTextureFromSurface(renderer, starsSurface);
    renderCopyScaled(renderer, starsTexture, NULL, NULL);

    SDL_DestroyTexture(starsTexture);
}

void stars_init(Stars *stars)
{
    int const minval = RGB_MAXIMUM * 130 / 150;
    int const midval = RGB_MAXIMUM * 130 / 100;
    int const maxval = RGB_MAXIMUM * 130 / 60;

    // compute the values for each of 4 possible star values
    uint8_t const starmap[4] = {
        0,
        minval,
        minval + (255 - minval) * (midval - minval) / (maxval - minval),
        255
    };

    // generate the colors for the stars
    for (int i = 0; i < 64; i++) {
        uint8_t bit0, bit1;

        // bit 5 = red @ 150 Ohm, bit 4 = red @ 100 Ohm
        bit0 = BIT(i, 5);
        bit1 = BIT(i, 4);
        int const r = starmap[(bit1 << 1) | bit0];

        // bit 3 = green @ 150 Ohm, bit 2 = green @ 100 Ohm
        bit0 = BIT(i, 3);
        bit1 = BIT(i, 2);
        int const g = starmap[(bit1 << 1) | bit0];

        // bit 1 = blue @ 150 Ohm, bit 0 = blue @ 100 Ohm
        bit0 = BIT(i, 1);
        bit1 = BIT(i, 0);
        int const b = starmap[(bit1 << 1) | bit0];

        // set the RGB color
        stars->star_color[i] = rgb(r, g, b);
    }

    for (int i = 0; i < STAR_COUNT; i++) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int color = rand() % 0x3f;
        Star star = { x, y, color };
        stars->stars[i] = star;
    }
}
