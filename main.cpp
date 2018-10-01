#include <iostream>
#include <SDL.h>
#include "suzanne_vertices.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define PIXEL_SCALE 100;

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;

void dibujaLineaRecta(point2d origen, point2d destino) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int x1 = origen.x;
    int y1 = origen.y;

    int x2 = destino.x;
    int y2 = destino.y;

    float y_diff = destino.y - origen.y;
    float x_diff = destino.x - origen.x;

    if (origen.x > destino.x) {
        x1 = destino.x;
        y1 = destino.y;

        x2 = origen.x;
        y2 = origen.y;
    }

    // m = pendiente
    float m = (y_diff/x_diff);

    // izquierda derecha
    for (int i = x1; i < x2; i++) {
        int px = i;
        int py = m * (px-x1) + y1;
        SDL_RenderDrawPoint(renderer, px, py);
    }

    // Reseteamos los valores originales
    x1 = origen.x;  y1 = origen.y;
    x2 = destino.x; y2 = destino.y;

    if (y1 > y2) {
        x1 = destino.x; y1 = destino.y;
        x2 = origen.x; y2 = origen.y;
    }

    // de arriba a abajo
    for (int i = y1; i < y2; i++) {
        int py = i;
        int px = (py-y1) / m  + x1;
        SDL_RenderDrawPoint(renderer, px, py);
    }
}

vertice mueveVertice(vertice v, float x, float y, float z)
{
    vertice vt;
    vt.x = v.x + x;
    vt.y = v.y + y;
    vt.z = v.z + z;

    return vt;
}

point2d perspectiveDivision(vertice v)
{
    point2d p;

    // Nos aseguramos de aplicar el pixel_scale por si z fuese cero.
    p.x = v.x * PIXEL_SCALE;
    p.y = v.y * PIXEL_SCALE;

    if (v.z != 0) {
        p.x = (v.x / v.z) * PIXEL_SCALE;
        p.y = (v.y / v.z) * PIXEL_SCALE;
    }

    // Centramos el punto en pantalla
    p.x+= WINDOW_WIDTH/2;
    p.y+= WINDOW_HEIGHT/2;

    return p;
}

void dibujarPixeles() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Dibujamos cada vértice en el render
    for (int i = 0; i<=1448; i++) {
        vertice v3d = mueveVertice(v[i], 0, 0, 1.5);
        point2d p = perspectiveDivision(v3d);
        SDL_RenderDrawPoint(renderer, p.x, p.y);
    }

}

void dibujarTriangulos() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Dibujamos cada vértice en el render
    for (int i = 0; i<=967; i++) {
        vertice v1, v2, v3;

        v1 = t[i].a;
        v2 = t[i].b;
        v3 = t[i].c;

        v1 = mueveVertice(v1, 0, 0, 1.5);
        v2 = mueveVertice(v2, 0, 0, 1.5);
        v3 = mueveVertice(v3, 0, 0, 1.5);

        point2d p1 = perspectiveDivision(v1);
        point2d p2 = perspectiveDivision(v2);
        point2d p3 = perspectiveDivision(v3);

        SDL_RenderDrawPoint(renderer, p1.x, p1.y);
        SDL_RenderDrawPoint(renderer, p2.x, p2.y);
        SDL_RenderDrawPoint(renderer, p3.x, p3.y);


        dibujaLineaRecta(p1, p2);
        dibujaLineaRecta(p1, p3);
        dibujaLineaRecta(p2, p3);

    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    loadVertices();
    loadTriangles();

    // Limpiamos la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //dibujarPixeles();
    dibujarTriangulos();
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
