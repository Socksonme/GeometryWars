#include <string>
#include "SDL2/SDL.h"
#ifndef HERO_H_
#define HERO_H_



class Hero {
    public:
        SDL_Rect rect;
        void Draw();
        // i hate this | (passing x, y, w and h, instead of an SDL_Rect)
        //             v
        void Init(int x, int y, int w, int h, std::string tex_path, SDL_Renderer* rend, SDL_RendererFlip rend_flip = SDL_FLIP_NONE, int ang = 0);
        void Move(const Uint8* state, int width, int height);

    private:
        int angle;
        SDL_RendererFlip flip;
        SDL_Texture* tex;
        SDL_Renderer* renderer;
        std::string path;
        void SetTexture();
        int vel = 0;
};

#endif // HERO_H_
