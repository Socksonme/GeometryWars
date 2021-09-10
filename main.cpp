#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "src/globals.h"
#include "src/Hero.h"
#include "src/Bullet.h"
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
    SDL_Texture* hero_tex = loadTextureFromBMP("assets/images/hero.bmp", main_renderer);

    SDL_Texture* enemy_tex1 = loadTextureFromBMP("assets/images/enemy1.bmp", main_renderer);
    SDL_Texture* enemy_tex2 = loadTextureFromBMP("assets/images/enemy2.bmp", main_renderer);

    Hero h1;
    h1.Init(20, 20, 55, 52, hero_tex, main_renderer, SDL_FLIP_NONE, 0);


    std::vector<Enemy*> enemies;
    for (int i = 0; i < 10; i++) {
        Enemy* enemy = new Enemy();
        enemy -> Init(rand() % mode.w, rand() % mode.h, 55, 52, enemy_tex1, main_renderer, SDL_FLIP_NONE, 0);
        enemies.push_back(enemy);
    }

    for (int i = 0; i < 5; i++) {
        Enemy* enemy = new EnemyFast();
        enemy -> Init(rand() % mode.w, rand() % mode.h, 55, 52, enemy_tex2, main_renderer, SDL_FLIP_NONE, 0);
        enemies.push_back(enemy);
    }

    std::vector<Bullet*> bullets;
    Bullet* new_bullet = nullptr;
    SDL_Texture* bullet_img = loadTextureFromBMP("assets/images/bullet.bmp", main_renderer);

    SDL_Event evt;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    while (true) {
        SDL_PollEvent(&evt);

        SDL_RenderClear(main_renderer);

        // build scene
        SDL_RenderCopy(main_renderer, background, 0, 0);
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i] -> Draw();
        }
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i] -> Draw();
        }
        h1.Draw();
        // render scene
        SDL_RenderPresent(main_renderer);

        h1.Move(state, mode.w, mode.h);

        for (int i = 0; i < enemies.size(); i++) {
            enemies[i] -> Move(h1, mode.w, mode.h);
        }
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i] -> Move();
        }
        if (state[SDL_SCANCODE_SPACE]) {
            new_bullet = new Bullet(main_renderer, bullet_img, h1.rect.x + h1.rect.w / 2, h1.rect.y + h1.rect.h / 2, h1.angle, h1.vel * 2);
            bullets.push_back(new_bullet);
        }


        SDL_Delay(25);
    }
    for (int i = 0; i < enemies.size(); i++) {
        delete (enemies[i]);
    }
    enemies.clear();
    for (int i = 0; i < bullets.size(); i++) {
        delete (bullets[i]);
    }
    bullets.clear();

    SDL_DestroyRenderer(main_renderer);
    main_renderer = nullptr;

    SDL_DestroyWindow(main_window);
    main_window = nullptr;



    SDL_Quit();
    return 0;
}

