#include "Entity.h"
#include "globals.h"
#include "SDL2/SDL.h"
#include <iostream>

void Entity::Draw() {
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, flip);
}
