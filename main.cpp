#include <iostream>
#include <SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

struct point2d {
    float x;
    float y;
};

int main() {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    // Limpiamos la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    point2d a, b;
    a.x = 10; a.y = 10;
    b.x = 30; b.y = 300;

    float y_diff = b.y - a.y;
    float x_diff = b.x - a.x;

    // m = pendiente
    float m = (y_diff/x_diff);

    // izquierda derecha
    for (int i = a.x; i < b.x; i++) {
        int px = i;
        int py = m * (px-a.x) + a.y;
        SDL_RenderDrawPoint(renderer, px, py);
    }

    // de arriba a abajo
    for (int i = a.y; i < b.y; i++) {
        int py = i;
        int px = (py-a.y) / m  + a.x;
        SDL_RenderDrawPoint(renderer, px, py);

    }
    SDL_RenderPresent(renderer);

    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
