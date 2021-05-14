#ifndef RENDER_H_
#define RENDER_H_

#include <SDL.h>
#include <SDL_image.h>

//Screen dimension constants
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 256

// Scale final screen
#define SCALE 3

// Globals
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *everythingTexture;
extern SDL_Surface *starsSurface;

void renderCopyScaled(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);
void render_init();
void render_destroy();

#endif /* RENDER_H_ */
