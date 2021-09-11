#include "Hero.h"
#include "globals.h"
#include <math.h>

void Hero::Init(int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend, SDL_RendererFlip rend_flip, int ang) {
    rect = {x, y, w, h};

    renderer = rend;

    flip = rend_flip;
    angle = ang;

    texture = tex;

}
void Hero::Move(const Uint8* state, int width, int height) {
    bool w_or_s = false;

    if (state[SDL_SCANCODE_W]) {
        w_or_s = true;
        vel += 2;
    }
    if(state[SDL_SCANCODE_S]) {
        w_or_s = true;
        vel -= 2;
    }
    if(state[SDL_SCANCODE_A]) {
        angle -= 5;
    }
    if(state[SDL_SCANCODE_D]) {
        angle += 5;
    }

    if (vel < max_vel * -1) {
        vel = -10;
    }
    else if (vel > max_vel) {
        vel = 10;
    }
    // if you're not currently moving
    if (vel < 0 && !(w_or_s)) {
        vel += 2;
    }
    else if (vel > 0 && !(w_or_s)) {
        vel -= 2;
    }

    // move amount
    rect.y += std::sin((angle - 90) * PI / 180) * vel;
    rect.x += std::cos((angle - 90) * PI / 180) * vel;

    if (rect.x < 0) {
         rect.x = 0;
    }
    else if (rect.x + rect.w > width) {
        rect.x = width - rect.w;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    else if (rect.y + rect.h > height) {
        rect.y = height - rect.h;
    }
}


