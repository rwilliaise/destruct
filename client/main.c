
#include "sh_scene.h"
#include "r_shared.h"
#include "r_window.h"

void r_MsgBoxError(const char *message) {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL) < 0) {
        fprintf(stderr,  "%s\n", message);
    }
}

int main(int argv, char** args) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        r_MsgBoxError("Failed to init SDL!");
        return -1;
    }

    r_Window window;

    sh_Scene scene = {0};

    if (r_WindowInit(&window) < 0) {
        r_MsgBoxError("Failed to init window!");
        return -1;
    }

    SDL_Event e;

    while (window.running != 0) {
        while (SDL_PollEvent(&e) != 0) {
            r_WindowHandleEvent(&window, &e);
        }
    }

    sh_SceneDestroy(&scene);

    r_WindowCleanup(&window);
    SDL_Quit();

    return 0;
}
