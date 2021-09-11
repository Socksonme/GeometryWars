#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "src/globals.h"
#include "src/Hero.h"
#include "src/Bullet.h"
#include "src/Enemy.h"
#include "src/Enemy_fast.h"


SDL_Texture* loadTextureFromBMP(const char* path, SDL_Renderer* renderer);
int main(int agrc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
        std::cout << "Mixer problem: " << Mix_GetError() << std::endl;
    }
    Mix_Music* background_music;
    Mix_Chunk* fire_sound;

    background_music = Mix_LoadMUS("assets/music/music.mp3");
    Mix_PlayMusic(background_music, -1);
    Mix_VolumeMusic(20);

    fire_sound = Mix_LoadWAV("assets/music/fire.wav");
    Mix_VolumeChunk(fire_sound, 20);

    SDL_DisplayMode mode;
    for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
        if (!(SDL_GetCurrentDisplayMode(i, &mode))) {
            break;
        }
    }

    SDL_Window* main_window = SDL_CreateWindow("Geometry", 0, 0, mode.w, mode.h, 0);
    SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("assets/fonts/ChronoType.ttf", 20);
    if (font == NULL) {
        std::cout << TTF_GetError() << std::endl;
    }
    SDL_Color text_color = {255, 255, 255};
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, "Hello, world!", text_color);
    SDL_Texture* text_img = SDL_CreateTextureFromSurface(main_renderer, text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect text_pos = {20, 20, 0, 0};
    SDL_QueryTexture(text_img, NULL, NULL, &text_pos.w, &text_pos.h);




    // Get textures
    SDL_Texture* background = loadTextureFromBMP("assets/images/background.bmp", main_renderer);
    SDL_Texture* hero_tex = loadTextureFromBMP("assets/images/hero.bmp", main_renderer);
    SDL_Texture* bullet_tex = loadTextureFromBMP("assets/images/bullet.bmp", main_renderer);
    SDL_Texture* enemy_tex1 = loadTextureFromBMP("assets/images/enemy1.bmp", main_renderer);
    SDL_Texture* enemy_tex2 = loadTextureFromBMP("assets/images/enemy2.bmp", main_renderer);

    // Initialize game objects
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

        SDL_RenderCopy(main_renderer, text_img, NULL, &text_pos);
        // render scene
        SDL_RenderPresent(main_renderer);

        h1.Move(state, mode.w, mode.h);

        for (int i = 0; i < enemies.size(); i++) {
            enemies[i] -> Move(h1, mode.w, mode.h);
        }
        for (std::vector<Bullet*>::iterator it = bullets.begin(); it < bullets.end(); it++) {
            if((*it) -> Move(mode.w, mode.h)) {
                delete((*it));
                it = bullets.erase(it);
            }
        }
        if (state[SDL_SCANCODE_SPACE]) {
            new_bullet = new Bullet(main_renderer, bullet_tex, h1.rect.x + h1.rect.w / 2, h1.rect.y + h1.rect.h / 2,
                                    h1.angle + ((rand() % 2 ? 1 : -1) * rand() % 5), h1.max_vel * 2);
            bullets.push_back(new_bullet);
            Mix_PlayChannel(-1, fire_sound, 0);
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


    TTF_Quit();
    SDL_Quit();
    return 0;
}

