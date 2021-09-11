#include "SDL2/SDL.h"
#ifndef GLOBALS_H_GWARS
#define GLOBALS_H_GWARS
const double PI = 3.14159;
SDL_Texture* loadTextureFromBMP(const char* path, SDL_Renderer* renderer);
int PointTo(SDL_Rect rect, int x, int y);
bool Collision(SDL_Rect r1, SDL_Rect r2);


#endif // GLOBALS_H_GWARS
