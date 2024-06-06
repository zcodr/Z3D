#include <iostream>
#include <SDL2/SDL.h>

#include "Player.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
	int width = 1152;
	int height = 648;
    SDL_Window* window = SDL_CreateWindow("ZPhysics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Player player = Player(width/2, height/2, 20);

    while(true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
              case SDL_QUIT:
                exit(0);
                break;

              default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
		
		player.update(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}