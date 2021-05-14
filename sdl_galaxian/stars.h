#ifndef STARS_H_
#define STARS_H_

#define STAR_COUNT 100
#define STAR_TIME_MS 32
#define RGB_MAXIMUM 224

typedef struct star_s {
    int x;
    int y;
    int color;
} Star;

typedef struct stars_s {
    Uint32 star_color[64];
    Star stars[STAR_COUNT];
} Stars;

void stars_init(Stars *stars);
void stars_render(Stars *stars);

#endif /* STARS_H_ */
