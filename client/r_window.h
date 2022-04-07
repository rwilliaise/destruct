#pragma once
#include "r_shared.h"

typedef struct {
    int running;
    SDL_Window *window;
    SDL_Surface *surface;
} r_Window;

int r_WindowInit(r_Window *window);
int r_WindowHandleEvent(r_Window *window, SDL_Event *event);
int r_WindowCleanup(r_Window *window);
