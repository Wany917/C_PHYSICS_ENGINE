#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

const int WIDTH = 1280;
const int HEIGHT = 1024;

int Circles_Rectangles(int nbCircles, int nbRectangles);

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius);

int main(int argc, char *argv[]) {

    int numCircles, numRectangles;
    printf("Enter number of circles to draw: ");
    scanf("%d", &numCircles);
    printf("Enter number of rectangles to draw: ");
    scanf("%d", &numRectangles);
    Circles_Rectangles(numCircles,numRectangles);
  
    return 0;
}

int Circles_Rectangles(int nbCircles, int nbRectangles)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       printf("Error initializing SDL: %s\n", SDL_GetError());
       return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Circles and Rectangles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int i;
    for (i = 0; i < nbCircles; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        drawCircle(renderer, rand() % WIDTH, rand() % HEIGHT, rand() % 50 + 50);
    }

    for (i = 0; i < nbRectangles; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        int w = rand() % 100 + 50;
        int h = rand() % 100 + 50;
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderDrawRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
    //attente de la fermeture de la fenêtre
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    //nettoyage et fin de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius) 
{
    int x1, y1, x2, y2;
    double angle;
    for (angle = 0; angle < 360; angle += 0.1) {
        x1 = x + (cos(angle) * radius);
        y1 = y + (sin(angle) * radius);
        x2 = x + (cos(angle + 0.1) * radius);
        y2 = y + (sin(angle + 0.1) * radius);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}