#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

const int WIDTH = 800;
const int HEIGHT = 600;

// Structure pour stocker les informations sur les formes
typedef struct {
    SDL_Rect rect; // rectangle
    SDL_Point triangle[3]; // triangle
    int radius; // cercle
    SDL_Color color; // couleur
    int xVel, yVel; // vitesse de déplacement sur l'axe x et y
} Shape;

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Simulateur de physique graphique", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (!window) {
        printf("Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialisation des formes
    Shape triangle = { { 0, 0, 100, 100 }, { { 50, 0 }, { 0, 100 }, { 100, 100 } }, 0, { 255, 0, 0, 255 }, 2, 2 };
    Shape rectangle = { { 150, 150, 100, 100 }, { { 0, 0 }, { 0, 0 }, { 0, 0 } }, 0, { 0, 255, 0, 255 }, 3, 3 };
    Shape circle = { { 300, 300, 100, 100 }, { { 0, 0 }, { 0, 0 }, { 0, 0 } }, 50, { 0, 0, 255, 255 }, 4, 4 };

    // Boucle principale
    while (1) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto cleanup;
            }
        }

        // Déplacement des formes
        triangle.rect.x += triangle.xVel;
        triangle.rect.y += triangle.yVel;
        rectangle.rect.x += rectangle.xVel;
        rectangle.rect.y += rectangle.yVel;
        circle.rect.x += circle.xVel;
        circle.rect.y += circle.yVel;

        // Vérification des collisions
                if (SDL_HasIntersection(&triangle.rect, &rectangle.rect)) {
            triangle.xVel = -triangle.xVel;
            triangle.yVel = -triangle.yVel;
            rectangle.xVel = -rectangle.xVel;
            rectangle.yVel = -rectangle.yVel;
        }
        if (SDL_HasIntersection(&triangle.rect, &circle.rect)) {
            triangle.xVel = -triangle.xVel;
            triangle.yVel = -triangle.yVel;
            circle.xVel = -circle.xVel;
            circle.yVel = -circle.yVel;
        }
        if (SDL_HasIntersection(&rectangle.rect, &circle.rect)) {
            rectangle.xVel = -rectangle.xVel;
            rectangle.yVel = -rectangle.yVel;
            circle.xVel = -circle.xVel;
            circle.yVel = -circle.yVel;
        }


        // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessin des formes
        SDL_SetRenderDrawColor(renderer, triangle.color.r, triangle.color.g, triangle.color.b, triangle.color.a);
        SDL_RenderDrawLines(renderer, triangle.triangle, 3);
        SDL_SetRenderDrawColor(renderer, rectangle.color.r, rectangle.color.g, rectangle.color.b, rectangle.color.a);
        SDL_RenderFillRect(renderer, &rectangle.rect);
        SDL_SetRenderDrawColor(renderer, circle.color.r, circle.color.g, circle.color.b, circle.color.a);
        SDL_RenderFillCircle(renderer, &circle.rect, circle.radius);

        // Mise à jour de l'écran
        SDL_RenderPresent(renderer);

        // Pause de 30 ms
        SDL_Delay(30);
    }

cleanup:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
