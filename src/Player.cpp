#include "Player.hpp"
#include "SDLCustom.hpp"

Player::Player(float x, float y, float width) {
    this->x = x;
    this->y = y;
    this->width = width;
}

void Player::update(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillCircle(renderer, x, y, width);
}