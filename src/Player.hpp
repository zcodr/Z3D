#include <SDL2/SDL.h>

class Player {
  public:
    float x, y;
    float width;

    Player(float x, float y, float width);
    void update(SDL_Renderer* renderer);
};