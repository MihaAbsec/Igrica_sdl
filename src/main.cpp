#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        cout << "Failed to create window\n";
        SDL_Quit();
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    if (!window_surface) {
        cout << "Failed to get the surface from the window\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool running = true;
    SDL_Event event;

    // Get initial position of the window
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;  // Close window when Escape is pressed
                }
                if (event.key.keysym.sym == SDLK_a) {
                    x -= 20;  
                    SDL_SetWindowPosition(window, x, y);
                }
                if (event.key.keysym.sym == SDLK_d) {
                    x += 20;  
                    SDL_SetWindowPosition(window, x, y);
                }
                if (event.key.keysym.sym == SDLK_w) {
                    y -= 20;
                    SDL_SetWindowPosition(window, x, y);
                }
                if (event.key.keysym.sym == SDLK_s) {
                    y += 20;
                    SDL_SetWindowPosition(window, x, y);
                }
            }
        }

        SDL_UpdateWindowSurface(window); // Update surface if needed
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

