#include <string>
#include "SDL2/SDL.h"
#include "Hero.h"
#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy {
    public:
        SDL_Rect rect;
        void Draw();
        virtual void Move(Hero player, int width, int height);
        void Init(int x, int y, int w, int h, std::string tex_path, SDL_Renderer* rend, SDL_RendererFlip rend_flip = SDL_FLIP_NONE, int ang = 0);
    protected:
        int angle;
        SDL_RendererFlip flip;
        SDL_Texture* tex;
        SDL_Renderer* renderer;
        std::string path;
        void SetTexture();
        int x_vel = 0;
        int y_vel = 0;
};



#endif // ENEMY_H_
