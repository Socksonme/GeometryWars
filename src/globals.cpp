#include "SDL2/SDL.h"
#include "globals.h"
#include <math.h>
#include <algorithm>
SDL_Texture* loadTextureFromBMP(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* tmp = SDL_LoadBMP(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    return tex;
}
int PointTo(SDL_Rect rect, int x, int y) {
    int x_dist = std::abs(rect.x - x);
    int y_dist = std::abs(rect.y - y);

    // Q1 || Q4
    if (rect.x < x) {
        /// Q1
        if (rect.y < y) {
            // ++ quadrant
        }
        //Q4
        else {
            // +- quadrant
            y_dist *= -1;
        }
    }
    // Q2 || Q3
    else {
        // Q2
        if (rect.y < y) {
            x_dist *= -1;
        }
        // Q3
        else {
            x_dist *= -1;
            y_dist *= -1;
        }
    }
    return (std::round(std::atan2(y_dist, x_dist) * (180 / PI)) + 90);
}
bool Collision(SDL_Rect r1, SDL_Rect r2) {
    int top    = std::min(r1.y, r2.y);
    int bottom = std::max(r1.y + r1.h, r2.y + r2.h);

    int left    = std::min(r1.x, r2.x);
    int right   = std::max(r1.x + r1.w, r2.x + r2.w);

    if (bottom-top > r1.h + r2.h)  {return false;}
    if (right-left > r1.w + r2.w) {return false;}

    return true;
}
