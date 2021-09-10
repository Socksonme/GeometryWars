#include "Hero.h"
#include "globals.h"

void Hero::Init(int x, int y, int w, int h, std::string tex_path, SDL_Renderer* rend, SDL_RendererFlip rend_flip, int ang) {
    rect = {x, y, w, h};

    path = tex_path;
    renderer = rend;

    flip = rend_flip;
    angle = ang;

    SetTexture();

}
void Hero::Move(int direction, int width, int height) {
    switch(direction) {
        case MOVE_UP:
            rect.y -= 5;
            break;
        case MOVE_DOWN:
            rect.y += 5;
            break;
        case MOVE_LEFT:
            rect.x -= 5;
            break;
        case MOVE_RIGHT:
            rect.x += 5;
            break;

    }
    // temporary
    angle++;
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
