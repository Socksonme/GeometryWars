#include "SDL2/SDL.h"
#include "globals.h"
SDL_Texture* loadTextureFromBMP(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* tmp = SDL_LoadBMP(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    return tex;
}
