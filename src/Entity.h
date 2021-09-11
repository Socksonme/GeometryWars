#include "SDL2/SDL.h"
#include "globals.h"
#ifndef ENTITY_H
#define ENTITY_H


class Entity {
    public:
        Entity() = default;
        SDL_Rect rect;
        int angle;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        void Draw();
    protected:
        SDL_RendererFlip flip;
};

#endif // ENTITY_H
