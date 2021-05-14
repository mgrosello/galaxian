#include "render.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *everythingTexture;
SDL_Surface *starsSurface;

void renderCopyScaled(SDL_Renderer *renderer,
    SDL_Texture *texture,
    const SDL_Rect *srcrect,
    const SDL_Rect *dstrect)
{
    if (dstrect != NULL) {
        SDL_Rect dstrectScaled = { dstrect->x * SCALE, dstrect->y * SCALE, dstrect->w * SCALE, dstrect->h * SCALE };
        SDL_RenderCopy(renderer, texture, srcrect, &dstrectScaled);
    } else {
        SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    }
}

void render_init()
{
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, 0, &window, &renderer);

    SDL_Surface *everythingSurface = IMG_Load("gfx/everything.png");
    Uint32 colorkey = SDL_MapRGB(everythingSurface->format, 0, 0, 0); // Color transparente = negro
    SDL_SetColorKey(everythingSurface, SDL_TRUE, colorkey);

    everythingTexture = SDL_CreateTextureFromSurface(renderer, everythingSurface);

    starsSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
}

void render_destroy()
{
    SDL_DestroyTexture(everythingTexture);
}
