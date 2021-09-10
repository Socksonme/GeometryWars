#include "SDL2/SDL.h"
#ifndef BULLET_H_
#define BULLET_H_

class Bullet {
    public:
        Bullet(SDL_Renderer* rend, SDL_Texture* tex, int x, int y, int ang, int vl);

        SDL_Renderer* renderer;
        SDL_Texture* texture = nullptr;

        SDL_Rect rect = {0, 0, 5, 10};
        int vel;
        int angle;
        void Move();
        void Draw();
};

#endif // BULLET_H_