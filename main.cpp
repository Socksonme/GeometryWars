#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "src/globals.h"
#include "src/Hero.h"
#include "src/Enemy.h"
#include "src/Enemy_fast.h"


SDL_Texture* loadTextureFromBMP(const char* path, SDL_Renderer* renderer);
int main(int agrc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* main_window = nullptr;
    SDL_Renderer* main_renderer = nullptr;

    SDL_Texture* background = nullptr;

    SDL_DisplayMode mode;
    for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
        if (!(SDL_GetCurrentDisplayMode(i, &mode))) {
            break;
        }
    }
    main_window = SDL_CreateWindow("Geometry", 0, 0, mode.w, mode.h, 0);
    main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

    background = loadTextureFromBMP("assets/images/background.bmp", main_renderer);

    Hero h1;
    h1.Init(20, 20, 55, 52, "assets/images/hero.bmp", main_renderer, SDL_FLIP_NONE, 135);
    std::vector<Enemy*> enemies;
    for (int i = 0; i < 10; i++) {
        Enemy* enemy = new Enemy();
        enemy -> Init(rand() % mode.w, rand() % mode.h, 55, 52, "assets/images/enemy1.bmp", main_renderer, SDL_FLIP_NONE, 0);
        enemies.push_back(enemy);
    }

    for (int i = 0; i < 5; i++) {
        Enemy* enemy = new EnemyFast();
        enemy -> Init(rand() % mode.w, rand() % mode.h, 55, 52, "assets/images/enemy2.bmp", main_renderer, SDL_FLIP_NONE, 0);
        enemies.push_back(enemy);
    }

    SDL_Event evt;
    while (true) {

        SDL_RenderClear(main_renderer);

        // build scene
        SDL_RenderCopy(main_renderer, background, 0, 0);
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i] -> Draw();
        }
        h1.Draw();
        // render scene
        SDL_RenderPresent(main_renderer);

        h1.Move(MOVE_DOWN, mode.w, mode.h);
        h1.Move(MOVE_RIGHT, mode.w, mode.h);

        for (int i = 0; i < enemies.size(); i++) {
            enemies[i] -> Move(h1, mode.w, mode.h);
        }


        SDL_Delay(25);
    }
    for (int i = 0; i < enemies.size(); i++) {
        delete (enemies[i]);
    }
    enemies.clear();

    SDL_DestroyRenderer(main_renderer);
    main_renderer = nullptr;

    SDL_DestroyWindow(main_window);
    main_window = nullptr;



    SDL_Quit();
    return 0;
}

