#include "TextureManager.hpp"
#include "ECSManager.hpp"
#include "EntityComponents/Transform.h"
#include "EntityComponents/Texture.h"
#include "EntityComponents/Animations.h"
#include "EntityComponents/PlayerController.h"
int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    TextureManager::init_windowing("test", 1000, 1000);
    bool quit = false;
    ECSManager ecs_manager;
    entt::entity box = ecs_manager.registry.create();
    SDL_Rect box_dimensions = {10, 10, 40, 40}; 
    ecs_manager.registry.emplace<Transform>(box, box_dimensions, true);
    ecs_manager.registry.emplace<PlayerController>(box);
    while(!quit){
        TextureManager::clear(0, 0, 0, 255);
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


/*
        entt::entity man = ecs_manager.registry.create();
        SDL_Rect man_dimensions = {430, 100, 400, 400};
        ecs_manager.registry.emplace<Transform>(man, man_dimensions, false);
        SDL_Texture* texture = TextureManager::load_image("assets/player.png");
        SDL_Rect texture_source_rect = {0, 0, 32, 32};
        ecs_manager.registry.emplace<Texture>(man, texture, texture_source_rect);
        ecs_manager.registry.emplace<Animations>(man, 32, 32, 4);
*/
        ecs_manager.update();
        TextureManager::present();
    }
    return 0;
}