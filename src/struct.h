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

// Shape Size
Shape shapes[100];
// Shape count
int shape_count = 0;