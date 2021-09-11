#include <string>
#include "SDL2/SDL.h"
#include "Hero.h"
#include "Entity.h"
#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy : public Entity {
    public:
        virtual void Move(Hero player, int width, int height);
        void Init(int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend, SDL_RendererFlip rend_flip = SDL_FLIP_NONE, int ang = 0);
    protected:
        int x_vel = 0;
        int y_vel = 0;
};



#endif // ENEMY_H_
