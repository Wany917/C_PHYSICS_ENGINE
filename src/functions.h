#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool check_collision(Shape a, Shape b)
{
    int x1 = a.x + a.w / 2;
    int y1 = a.y + a.h / 2;
    int x2 = b.x + b.w / 2;
    int y2 = b.y + b.h / 2;
    // check dist & coordonate between two shapes
    // x1, y1, => coordonate du centre de ma forme a
    // x2, y2 =>  coordonate du centre de ma forme b

    int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    // Formule euclidienne
    int radius_sum = a.w / 2 + b.w / 2;

    // return true or false 
    return distance < radius_sum;
}

void draw_shape(SDL_Renderer *renderer, Shape shape)
{
    if (shape.is_circle)
    {
        // Define color 
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


    // Check the screen output
    if (shape->x <= 0 || shape->x + shape->w >= WIDTH)
    {
        shape->dx = -shape->dx;
    }

    if (shape->y <= 0 || shape->y + shape->h >= HEIGHT)
    {
        shape->dy = -shape->dy;
    }
}