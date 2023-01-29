// SDL TEST 1
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Welcome", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Font *font = TTF_OpenFont("../arial/arial.ttf", 24);

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x;
                int y = event.button.y;
                if (x > 100 && x < 500 && y > 100 && y < 150)
                {
                    // Launch button clicked
                    printf("Program is launching...\n");
                    // Insert code for program here
                }
                else if (x > 100 && x < 500 && y > 200 && y < 250)
                {
                    // Quit button clicked
                    printf("Exiting program...\n");
                    running = 0;
                }
                else if (x > 100 && x < 500 && y > 300 && y < 350)
                {
                    // Info button clicked
                    printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam velit ipsum, molestie vel risus et, malesuada bibendum augue. Sed euismod malesuada tempor. Fusce eget hendrerit augue.\n");
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw launch button
        surface = TTF_RenderText_Solid(font, "Launch", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.x = 100;
        rect.y = 100;
        rect.w = 400;
        rect.h = 50;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // Draw quit button
        surface = TTF_RenderText_Solid(font, "Quit", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.x = 100;
        rect.y = 200;
        rect.w = 400;
        rect.h = 50;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // Draw info button
        surface = TTF_RenderText_Solid(font, "Info", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.x = 100;
        rect.y = 300;
        rect.w = 400;
        rect.h = 50;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}