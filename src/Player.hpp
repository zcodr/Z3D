#include <SDL2/SDL.h>

class Player {
  public:
    float x, y;
    float width;
	float speed;
	float turning_speed;
	float direction;
	float fov;

    Player(float x, float y, float width, float speed, float turning_speed, float direction, float fovj);
    void update(SDL_Renderer* renderer, float walls[][4]);
    void move(bool backwards = false);
	void turn(bool way);
};