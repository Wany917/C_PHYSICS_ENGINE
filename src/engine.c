#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>


#include "defines.h"
#include "struct.h"
#include "functions.h"

int main()
{
    // Init SDL video
    SDL_Init(SDL_INIT_VIDEO);

    // Create window
    SDL_Window *window = SDL_CreateWindow("PHYSICS_ENGINE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
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
                // Initialize the shape position (x,y)
                shape.x = x - RADIUS / 2;
                shape.y = y - RADIUS / 2;
                // initialize the shape width and height
                shape.w = RADIUS;
                shape.h = RADIUS;
                // initialize the shape speed horizontal and vertical who is always constant
                shape.dx = SPEED;
                shape.dy = SPEED;
                // I define if the shape is a circle by default
                shape.is_circle = shape.is_circle;
                shape.color = (SDL_Color){0, 0, 255, 255};

                shapes[shape_count++] = shape;

                // To alternate my shape creation between square and rectangle I just have to pass this boolean to false
                shape.is_circle = !shape.is_circle;
            }


            // Condition who listen our keyboard events
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


        // Constantly update the shape mouv & draw the shape
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