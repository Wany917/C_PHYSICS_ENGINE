#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "defines.h"
#include "struct.h"
#include "functions.h"

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
                shape.is_circle = shape.is_circle;
                shape.color = (SDL_Color){0, 0, 255, 255};

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

quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}