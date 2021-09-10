#include <string>
#include "SDL2/SDL.h"
#include "Hero.h"
#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy {
    public:
        SDL_Rect rect;
        int angle;
        void Draw();
        virtual void Move(Hero player, int width, int height);
        void Init(int x, int y, int w, int h, SDL_Texture* texture, SDL_Renderer* rend, SDL_RendererFlip rend_flip = SDL_FLIP_NONE, int ang = 0);
    protected:
        SDL_RendererFlip flip;
        SDL_Texture* tex;
        SDL_Renderer* renderer;
        int x_vel = 0;
        int y_vel = 0;
};



#endif // ENEMY_H_
