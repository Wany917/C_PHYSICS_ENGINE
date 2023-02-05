#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#define WIDTH 640
#define HEIGHT 480
#define RADIUS 50
#define SPEED 2

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

bool check_collision(Shape a, Shape b)
{
    int x1 = a.x + a.w / 2;
    int y1 = a.y + a.h / 2;
    int x2 = b.x + b.w / 2;
    int y2 = b.y + b.h / 2;

    int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    int radius_sum = a.w / 2 + b.w / 2;

    return distance < radius_sum;
}

void draw_shape(SDL_Renderer *renderer, Shape shape)
{
    if (shape.is_circle)
    {
        SDL_SetRenderDrawColor(renderer, shape.color.r, shape.color.g, shape.color.b, shape.color.a);
        for (int w = 0; w < shape.w; w++)
        {
            for (int h = 0; h < shape.h; h++)
            {
                int dx = w - shape.w / 2;
                int dy = h - shape.h / 2;
                if ((dx * dx) + (dy * dy) < (shape.w / 2) * (shape.h / 2))
                {
                    SDL_RenderDrawPoint(renderer, shape.x + w, shape.y + h);
                }
            }
        }
    }
    else
    {
        SDL_Rect rect = {shape.x, shape.y, shape.w, shape.h};
        SDL_SetRenderDrawColor(renderer, shape.color.r, shape.color.g, shape.color.b, shape.color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void move_shape(Shape *shape)
{
    shape->x += shape->dx;
    shape->y += shape->dy;

    if (shape->x <= 0 || shape->x + shape->w >= WIDTH)
    {
        shape->dx = -shape->dx;
    }

    if (shape->y <= 0 || shape->y + shape->h >= HEIGHT)
    {
        shape->dy = -shape->dy;
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Formes interactives", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x;
                int y = event.button.y;

                Shape shape;
                shape.x = x - RADIUS / 2;
                shape.y = y - RADIUS / 2;
                shape.w = RADIUS;
                shape.h = RADIUS;
                shape.dx = SPEED;
                shape.dy = SPEED;
                shape.is_circle = true;
                shape.color = (SDL_Color){0, 0, 255, 255};

                shapes[shape_count++] = shape;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_r)
                {
                    shape_count = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < shape_count; i++)
        {
            for (int j = i + 1; j < shape_count; j++)
            {
                if (check_collision(shapes[i], shapes[j]))
                {
                    int temp_dx = shapes[i].dx;
                    int temp_dy = shapes[i].dy;

                    shapes[i].dx = shapes[j].dx;
                    shapes[i].dy = shapes[j].dy;

                    shapes[j].dx = temp_dx;
                    shapes[j].dy = temp_dy;
                }
            }

            move_shape(&shapes[i]);
            draw_shape(renderer, shapes[i]);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}