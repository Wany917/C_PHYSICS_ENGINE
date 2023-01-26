#include <SDL2/SDL.h>
#include <stdio.h>

// Taille de la fenêtre
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Déclarations des formes
SDL_Rect rectangles[16];

// Déclaration des vitesses
int RRectSpeed[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 , 16, 17};

// Pointeur de la fenêtre
SDL_Window* window = NULL;

// Pointeur de la surface de l'écran
SDL_Surface* screenSurface = NULL;

int main(int argc, char* args[]){

    // Initialisation de SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf("Erreur lors de l'initialisation de SDL. Erreur : %s\n", SDL_GetError());
    }
    else{
        // Création de la fenêtre
        window = SDL_CreateWindow("Simulateur de physique avec SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            printf("Erreur lors de la création de la fenêtre. Erreur : %s\n", SDL_GetError());
        }
        else{
            // Obtention de la surface de la fenetre
            screenSurface = SDL_GetWindowSurface(window);

            // Génération des rectangles
            for (int i=0; i<16; i++){
                rectangles[i].x = rand() % SCREEN_WIDTH;
                rectangles[i].y = rand() % SCREEN_HEIGHT;
                rectangles[i].w = 10;
                rectangles[i].h = 10;
            }

            // Boucle principale
            bool done = false;
            while(!done){
                // Gérer les événements
                // Tester la touche q
                SDL_Event event;
                while (SDL_PollEvent(&event)){
                    if (event.type == SDL_QUIT){
                        done = true;
                    }
                }

                // Re-dessiner le fond de la fenêtre
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

                // Dessiner les formes
                for (int i=0; i<16; i++){
                    SDL_FillRect(screenSurface, &rectangles[i], SDL_MapRGB(screenSurface->format, 0, 255, 0));
                }

                // Déplacer les formes
                for (int i=0; i<16; i++){
                    rectangles[i].x += RRectSpeed[i];
                    rectangles[i].y += RRectSpeed[i];
                }
                
                // Rebondir les formes sur les bords de de la fenêtre
                for(int i=0; i<16; i++){
                    if(rectangles[i].x >= SCREEN_WIDTH || rectangles[i].x <= 0){
                        RRectSpeed[i] = -RRectSpeed[i];
                    }
                    if (rectangles[i].y >= SCREEN_HEIGHT || rectangles[i].y <= 0){
                        RRectSpeed[i] = -RRectSpeed[i];
                    }
                }
                
                // Rebondir les formes entre elles
                for( int i=0; i<16; i++){
                    for( int j=0; j<16; j++){
                        if(i != j){                                                    
                            if(SDL_HasIntersection(&rectangles[i], &rectangles[j])){                                
                                RRectSpeed[i] = -RRectSpeed[i];
                                RRectSpeed[j] = -RRectSpeed[j];
                            }
                        }
                    }
                }

                //  Mettre à jour la fenêtre
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Libération des ressources et arrêt de SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}