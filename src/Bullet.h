#include "SDL2/SDL.h"
#ifndef BULLET_H_
#define BULLET_H_


class Bullet {
    public:
        Bullet(SDL_Renderer* rend, SDL_Texture* tex, int x, int y, int ang, int vl);

        SDL_Renderer* renderer;
        SDL_Texture* texture = nullptr;

        SDL_Rect rect = {0, 0, 5, 10};
        int health = 1;
        int vel;
        int angle;
        int lifetime = 1000;
        Uint32 start_time = SDL_GetTicks();
        int Move(int w, int h);
        void Draw();

};

#endif // BULLET_H_
