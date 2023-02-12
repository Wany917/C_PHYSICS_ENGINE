#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 780
#define RADIUS 50
#define SPEED 1

#define window_x SDL_WINDOWPOS_CENTERED
#define window_y SDL_WINDOWPOS_CENTERED

typedef struct Shape
{
    int x, y;
    int width, height;
    int dx, dy;
    bool is_circle;
    SDL_Color color;
} Shape;

Shape shape[10];
int shape_count = 0;

bool check_shape_colllision(Shape a, Shape b)
{
    int x_1 = a.x + a.width / 2;
    int y_1 = a.x + a.height / 2;
    int x_2 = b.x + a.width / 2;
    int y_2 = b.x + a.height / 2;

    int dist = sqrt(((x_2 - x_1) * (x_2 * x_1)) + ((y_2 - y_1) * (y_2 * y_1)));
    int radius_sum = a.width / 2 + b.width / 2;

    return dist < radius_sum;
}

void shape_draw(SDL_Renderer *renderer, Shape shape)
{
    if (shape.is_circle)
    {
        SDL_SetRenderDrawColor(renderer, shape.color.r, shape.color.g, shape.color.b, shape.color.a);
        for (int w = 0; w < shape.width; w++)
        {
            for (int h = 0; h < shape.height; h++)
            {
                int dx = w - shape.width / 2;
                int dy = h - shape.height / 2;
                if ((dx * dx) + (dy * dy) < (shape.width / 2) * (shape.height / 2))
                {
                    SDL_RenderDrawPoint(renderer, shape.x + w, shape.y + h);
                }
            }
        }
    }
    else
    {
        SDL_Rect rect = {shape.x, shape.y, shape.width, shape.height};
        SDL_SetRenderDrawColor(renderer, shape.color.r, shape.color.g, shape.color.b, shape.color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void shape_move(Shape *shape)
{
    shape->x = shape->dx;
    shape->y = shape->dy;

    if (shape->x <= 0 || shape->x + shape->width >= WIDTH)
    {
        shape->dx = -shape->dx;
    }
    if (shape->y <= 0 || shape->y + shape->height >= WIDTH)
    {
        shape->dy = -shape->dy;
    }
}

int main()
{
    int init = SDL_Init(SDL_INIT_VIDEO);

    if (init < 0)
    {
        printf("Cannot initialize SDL VIDEO : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = SDL_CreateWindow("PHYSICAL ENGINE", window_x, window_y, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // main loop
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

                shape.width = RADIUS;
                shape.height = RADIUS;

                shape.dx = SPEED;
                shape.dy = SPEED;

                shape.is_circle = shape.is_circle;
                shape.color = (SDL_Color){215, 157, 173, 22};

                shapes[shape_count++] = shape;
                shape.is_circle = !shape.is_circle;
            }

            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_r)
                {
                    shape_count = 0;
                }
                if (event.key.keysym.sym == SDLK_q)
                {
                    shape_count = 0;
                    goto quit;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < shape_count; i++)
        {
            for (int j = 0; j < shape_count; j++)
            {
                if (check_shape_colllision(shapes[i], shapes[j]))
                {
                    int tmp_dx = shapes[i].dx;
                    int tmp_dy = shapes[i].dy;

                    shapes[j].dx = tmp_dx;
                    shapes[j].dy = tmp_dy;
                    shapes[i].dx = shapes[j].dx;
                    shapes[i].dy = shapes[j].dy;
                }
            }

            shape_move(&shapes[i]);
            shape_draw(renderer, shapes[i]);
        }
        SDL_RenderPresent(renderer);
    }
quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}