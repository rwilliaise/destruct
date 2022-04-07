#include "r_window.h"

int r_WindowInit(r_Window *window) {
    if ((window->window = SDL_CreateWindow("Destruct", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)) == NULL) {
        return -2;
    }

    window->surface = SDL_GetWindowSurface(window->window);
    window->running = 1;
    return 0;
}

int r_WindowHandleEvent(r_Window *window, SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        window->running = 0;
    }

    return 0;
}

int r_WindowCleanup(r_Window *window) {
    SDL_DestroyWindow(window->window);
    return 0;
}
