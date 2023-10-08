#include <iostream>
#include <SDL3/SDL.h>
#include <sndfile.hh>
#include <stdio.h>
#include "AudioFile.h"

int main(int argc, char** argv)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return -1;
    }
    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Window",
        800, // Width
        600, // Height
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_MAXIMIZED
    );

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return -1;
    }

    // Event loop
    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // Render your content here
        // SDL_RenderClear(renderer); // If you want to clear the window
        // SDL_RenderPresent(renderer); // If you want to update the window
    }

    // Cleanup and quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}