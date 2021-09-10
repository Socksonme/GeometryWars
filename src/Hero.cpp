#include "Hero.h"
#include "globals.h"
#include <math.h>
#define PI 3.14159

void Hero::Init(int x, int y, int w, int h, std::string tex_path, SDL_Renderer* rend, SDL_RendererFlip rend_flip, int ang) {
    rect = {x, y, w, h};

    path = tex_path;
    renderer = rend;

    flip = rend_flip;
    angle = ang;

    SetTexture();

}
void Hero::Move(const Uint8* state, int width, int height) {
    x_vel = 0;
    y_vel = 0;
    if (state[SDL_SCANCODE_W]) {
        y_vel = -5;
    }
    if(state[SDL_SCANCODE_S]) {
        y_vel = 5;
    }
    if(state[SDL_SCANCODE_A]) {
        x_vel = -5;
    }
    if(state[SDL_SCANCODE_D]) {
        x_vel = 5;
    }
    angle = std::round(std::atan2(y_vel, x_vel) * (180 / PI)) + 90;
    rect.y += y_vel;
    rect.x += x_vel;
    // use atan2 for angle
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

void Hero::SetTexture() {
    tex = loadTextureFromBMP(path.c_str(), renderer);
}
void Hero::Draw() {
    SDL_RenderCopyEx(renderer, tex, NULL, &rect, angle, NULL, flip);
}
