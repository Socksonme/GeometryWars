#include <math.h>
#include "SDL2/SDL.h"
#include "Bullet.h"
#include "globals.h"

Bullet::Bullet(SDL_Renderer* rend, SDL_Texture* tex, int x, int y, int ang, int vl) {
    renderer = rend;
    texture = tex;

    rect.x = x;
    rect.y = y;

    angle = ang;
    vel = vl;
}
void Bullet::Draw() {
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}
void Bullet::Move() {
    rect.y += std::sin((angle - 90) * PI / 180) * vel;
    rect.x += std::cos((angle - 90) * PI / 180) * vel;
}
