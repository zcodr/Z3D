#include <SDL2/SDL.h>
#include <vector>

float min(float a, float b) {
    if (a < b) {
        return a;
    }
    return b;
}

float max(float a, float b) {
    if (a > b) {
        return a;
    }
    return b;
}

std::vector<float> intersection(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y) {
// Store the values for fast access and easy
// equations-to-code conversion
float x1 = p1x, x2 = p2x, x3 = p3x, x4 = p4x;
float y1 = p1y, y2 = p2y, y3 = p3y, y4 = p4y;
 
float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
// If d is zero, there is no intersection
if (d == 0) {

    return std::vector<float>(2, 1000000);
}
 
// Get the x and y
float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
// Check if the x and y coordinates are within both lines
if ( x < min(x1, x2) || x > max(x1, x2) ||
x < min(x3, x4) || x > max(x3, x4) ) return std::vector<float>(2, 1000000);
if ( y < min(y1, y2) || y > max(y1, y2) ||
y < min(y3, y4) || y > max(y3, y4) ) return std::vector<float>(2, 1000000);
 
// Return the point of intersection
float arr[] = {x, y};
return std::vector<float>(arr, arr + sizeof(arr) / sizeof(int));
}

int
SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


int
SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}