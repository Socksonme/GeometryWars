#include <math.h>
#include "SDL2/SDL.h"
#include "Bullet.h"
#include "globals.h"
#include <iostream>

Bullet::Bullet(SDL_Renderer* rend, SDL_Texture* tex, int x, int y, int ang, int vl) {
    renderer = rend;
    texture = tex;


    rect.x = x;
    rect.y = y;

    angle = ang;
    vel = vl;
}

int Bullet::Move(int w, int h) {
    rect.y += std::sin((angle - 90) * PI / 180) * vel;
    rect.x += std::cos((angle - 90) * PI / 180) * vel;
    if (SDL_GetTicks() >= start_time + lifetime) {
        return 1;
    }
    if (rect.x < 0) {
         return 1;
    }
    else if (rect.x + rect.w > w) {
        return 1;
    }
    else if (rect.y < 0) {
        return 1;
    }
    else if (rect.y + rect.h > h) {
        return 1;
    }
    return 0;
}
void Bullet::Draw() {
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}
