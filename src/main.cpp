#include <iostream>
#include <SDL3/SDL.h>
#include <sndfile.hh>
#include <stdio.h>
#include "AudioFile.h"

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Window *window;
    window = SDL_CreateWindow(
        "my window",
        320, 240, SDL_WINDOW_RESIZABLE);
    int i = 0;
    while (i < 100000)
    {
        i++;
    }
    SDL_Quit();
    return 0;
}