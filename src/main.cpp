#include "TextureManager.hpp"
#include "ECSManager.hpp"
#include "EntityComponents/Transform.h"
#include "EntityComponents/Texture.h"
#include "EntityComponents/Animations.h"
#include "EntityComponents/PlayerController.h"
#include "EntityComponents/Hitbox.h"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    TextureManager::init_windowing("test", 1000, 1000);
    bool quit = false;
    ECSManager ecs_manager;
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    Uint32 frame_start;
    int frame_time;
    entt::entity box = ecs_manager.registry.create();
    SDL_Rect box_dimensions = {10, 10, 40, 40}; 
    ecs_manager.registry.emplace<Transform>(box, box_dimensions, true);
    ecs_manager.registry.emplace<PlayerController>(box);
    SDL_Texture* texture = TextureManager::load_image("assets/player.png");
    SDL_Rect texture_source_rect = {0, 0, 32, 32};
    ecs_manager.registry.emplace<Texture>(box, texture, texture_source_rect);
    ecs_manager.registry.emplace<Animations>(box, 32, 32, 4);
    ecs_manager.registry.emplace<Hitbox>(box);

    while(!quit){
        frame_start = SDL_GetTicks();
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        
        default:
            break;
        }
        TextureManager::clear(0, 0, 0, 255);
        ecs_manager.update();
        TextureManager::present();
        frame_time = SDL_GetTicks() - frame_start;
        if(frame_delay > frame_time){
            SDL_Delay(frame_delay - frame_time);
        }
    }
    return 0;
}