#include "Player.hpp"
#include "SDLCustom.hpp"

Player::Player(float x, float y, float width, float speed, float turning_speed, float direction, float fov) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->speed = speed;
    this->turning_speed = turning_speed;
    this->direction = direction;
    this->fov = fov;
}

void Player::update(SDL_Renderer* renderer, float walls[][4]) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillCircle(renderer, x, y, width);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLineF(renderer, x, y, x + cos(direction) * width, y + sin(direction) * width);

    float conv = fov * 3.14 / 180;
    float draw_x = 0;
    float increment_x = 1152/(conv/0.01);
    
    for (float i = 0; i < conv; i += 0.01) {
        std::vector<float> result(2, 1000000);
        for (int i = 0; i < (4); i++) {
            std::vector<float> next = intersection(x, y, x + cos(i + direction - (conv/2)) * 2000, y + sin(i + direction - (conv/2)) * 2000, walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
            float next_dist = sqrt((x - next[0])*(x - next[0]) + (y - next[1])*(y - next[1]));
            float result_dist = sqrt((x - result[0])*(x - result[0]) + (y - result[1])*(y - result[1]));
            if (next_dist < result_dist) {
                result = next;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if (result[0] == 1000000 && result[1] == 1000000) {
            SDL_RenderDrawLineF(renderer, x, y, x + cos(i + direction - (conv/2)) * 2000, y + sin(i + direction - (conv/2)) * 2000);
        }
        else {
            SDL_RenderDrawLineF(renderer, x, y, result[0], result[1]);
        }

        float distance = sqrt((x - result[0])*(x - result[0]) + (y - result[1])*(y - result[1]));
        distance = distance * cos(i + - (conv/2));
        float height = 32000/distance;
        SDL_FRect rect;
        rect.x = draw_x;
        rect.y = 324 - height/2;
        rect.w = increment_x;
        rect.h = height;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRectF(renderer, &rect);
        draw_x += increment_x;
    }
}

void Player::move(bool backwards) {
    if (backwards) {
        x -= cos(direction) * speed;
        y -= sin(direction) * speed;
    }
    else {
        x += cos(direction) * speed;
        y += sin(direction) * speed;
    }
}

// true = left, false = right
void Player::turn(bool way) {
    if (way) {
        direction -= turning_speed;
    }
    else {
        direction += turning_speed;
    }
}