#include "Enemy.h"
#include "Hero.h"
#include "globals.h"
void Enemy::Init(int x, int y, int w, int h, std::string tex_path, SDL_Renderer* rend, SDL_RendererFlip rend_flip, int ang) {
    rect = {x, y, w, h};

    path = tex_path;
    renderer = rend;

    flip = rend_flip;
    angle = ang;

    SetTexture();
}
void Enemy::Move(Hero player, int width, int height) {

    if (!y_vel) {
        switch (rand() % 2) {
            case 0:
                y_vel = -1;
                break;
            case 1:
                y_vel = 1;
                break;
        }
    }

    if (!x_vel) {
        switch (rand() % 2) {
            case 0:
                x_vel = -1;
                break;
            case 1:
                x_vel = 1;
                break;
        }
    }


    rect.x += x_vel;
    rect.y += y_vel;
    angle += 8;

    if (rect.x < 0) {
         x_vel *= -1;
         rect.x = 0;
    }
    else if (rect.x + rect.w > width) {
        x_vel *= -1;
        rect.x = width - rect.w;
    }
    if (rect.y < 0) {
        y_vel *= -1;
        rect.y = 0;
    }
    else if (rect.y + rect.h > height) {
        y_vel *= -1;
        rect.y = height - rect.h;
    }
}
void Enemy::SetTexture() {
    tex = loadTextureFromBMP(path.c_str(), renderer);
}
void Enemy::Draw() {
    SDL_RenderCopyEx(renderer, tex, NULL, &rect, angle, NULL, flip);
}
