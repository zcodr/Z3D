#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Player.hpp"

int main() {
    float walls[][4] = {{100, 50, 1052, 51}, {1052, 50, 1051, 598}, {1052, 598, 100, 597}, {100, 598, 101, 50}};

    SDL_Init(SDL_INIT_VIDEO);
	int width = 1152;
	int height = 648;
    SDL_Window* window = SDL_CreateWindow("ZPhysics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Player player = Player(width/2, height/2, 20, 0.1, 0.002, -1.57, 90);

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
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_UP]) {
            player.move();
        }
        if (keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_DOWN]) {
            player.move(true);
        }
        if (keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_LEFT]) {
            player.turn(true);
        }
        if (keystates[SDL_SCANCODE_D] || keystates[SDL_SCANCODE_RIGHT]) {
            player.turn(false);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
		
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        for (int i = 0; i < (sizeof(walls) / sizeof(walls[0])); i++) {
            SDL_RenderDrawLineF(renderer, walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
        }
		player.update(renderer, walls);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}