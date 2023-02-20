typedef struct Shape
{
    int x, y;
    int w, h;
    int dx, dy;
    bool is_circle;
    SDL_Color color;
} Shape;

Shape shapes[100];
int shape_count = 0;