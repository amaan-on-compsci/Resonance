#include <iostream>
#include <SDL3/SDL.h>
#include <sndfile.hh>
#include <stdio.h>
#include "AudioFile.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a resizable window
    SDL_Window* window = SDL_CreateWindow(
        "Waveform Visualizer",
        1000, 900,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set the initial background color (dark mode)
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (event.type >= SDL_EVENT_WINDOW_FIRST && event.type <= SDL_EVENT_WINDOW_LAST) {
                if (event.window.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
                    // Handle window resize
                    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}