#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Shape
{
    int x, y;
    int w, h;
    int dx, dy;
    bool is_circle;
    SDL_Color color;
} Shape;
