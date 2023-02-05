// #include <SDL2/SDL.h>
// #include <SDL2_gfxPrimitives.h>
// #include <time.h>
// #include <stdbool.h>

// #define WIDTH 800
// #define HEIGHT 600
// #define SPEED 1
// #define MAX_SHAPES 10

// // Structure pour stocker les informations de la forme
// typedef struct Shape {
//     int x, y;
//     int w, h;
//     int xvel, yvel;
//     bool isCircle;
// } Shape;

// int main() {
//     srand(time(NULL));

//     // Initialiser SDL
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init error: %s\n", SDL_GetError());
//         return 1;
//     }

//     // Créer la fenêtre
//     SDL_Window* window = SDL_CreateWindow("Formes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//     if (!window) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow error: %s\n", SDL_GetError());
//         SDL_Quit();
//         return 1;
//     }

//     // Créer le rendu
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (!renderer) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer error: %s\n", SDL_GetError());
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//         return 1;
//     }

//     // Événement pour la gestion des clics
//     SDL_Event event;

//     // Tableau de formes
//     Shape shapes[MAX_SHAPES];
//     int shapeCount = 0;

//     // Boucle principale
//     int running = 1;
//     while (running) {
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     running = 0;
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:
//                     if (shapeCount < MAX_SHAPES) {
//                         shapes[shapeCount].x = event.button.x - shapes[shapeCount].w / 2;
//                         shapes[shapeCount].y = event.button.y - shapes[shapeCount].h / 2;
//                         shapes[shapeCount].xvel = SPEED;
//                         shapes[shapeCount].yvel = SPEED;
//                         shapes[shapeCount].isCircle = rand() % 2;
//                                             if (shapes[shapeCount].isCircle) {
//                         shapes[shapeCount].w = shapes[shapeCount].h = rand() % 50 + 50;
//                     } else {
//                         shapes[shapeCount].w = rand() % 50 + 50;
//                         shapes[shapeCount].h = rand() % 50 + 50;
//                     }
//                     shapeCount++;
//                 }
//                 break;
//         }
//     }

//     // Effacer la fenêtre
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer);

//     // Dessiner les formes
//     for (int i = 0; i < shapeCount; i++) {
//         Shape* shape = &shapes[i];

//         if (shape->isCircle) {
//             filledCircleRGBA(renderer, shape->x + shape->w / 2, shape->y + shape->h / 2, shape->w / 2, 255, 0, 0, 255);
//         } else {
//             rectangleRGBA(renderer, shape->x, shape->y, shape->x + shape->w, shape->y + shape->h, 255, 0, 0, 255);
//         }

//         // Détecter les collisions entre les formes
//         for (int j = i + 1; j < shapeCount; j++) {
//             Shape* other = &shapes[j];
//             int left1 = shape->x, left2 = other->x;
//             int right1 = shape->x + shape->w, right2 = other->x + other->w;
//             int top1 = shape->y, top2 = other->y;
//             int bottom1 = shape->y + shape->h, bottom2 = other->y + other->h;

//             if (left1 > right2 || left2 > right1) continue;
//             if (top1 > bottom2 || top2 > bottom1) continue;

//             // Inverser les vitesses lorsqu'une collision est détectée
//             shape->xvel *= -1;
//             shape->yvel *= -1;
//             other->xvel *= -1;
//             other->yvel *= -1;
//         }

//         // Déplacer la forme
//         shape->x += shape->xvel;
//         shape->y += shape->yvel;

//         // Empêcher la forme de sortir de l'écran
//         if (shape->x < 0 || shape->x + shape->w > WIDTH) {
//             shape->xvel *= -1;
//         }
//         if (shape->y < 0 || shape->y + shape->h > HEIGHT) {
//             shape->yvel *= -1;
//         }
//     }

//     // Afficher la fenêtre
//     SDL_RenderPresent(renderer);
// }

// // Nettoyer les ressources
// SDL_DestroyRenderer(renderer);
// SDL_DestroyWindow(window);
// SDL_Quit();

// return 0;
// }
