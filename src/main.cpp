#include "TextureManager.hpp"
#include "ECSManager.hpp"
#include "EntityComponents/Transform.h"
#include "EntityComponents/Texture.h"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    TextureManager::init_windowing("test", 1000, 1000);
    bool quit = false;
    ECSManager ecs_manager;
    while(!quit){
        TextureManager::clear();
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

        entt::entity box = ecs_manager.registry.create();
        SDL_Rect box_dimensions = {100, 100, 400, 400}; 
        ecs_manager.registry.emplace<Transform>(box, box_dimensions, true);

        entt::entity grass = ecs_manager.registry.create();
        SDL_Rect grass_dimensions = {430, 100, 400, 400};
        ecs_manager.registry.emplace<Transform>(grass, grass_dimensions, false);
        SDL_Texture* texture = TextureManager::load_image("assets/grass.png");
        SDL_Rect texture_source_rect = {0, 0, 32, 32};
        ecs_manager.registry.emplace<Texture>(grass, texture, texture_source_rect);
        ecs_manager.update();
        TextureManager::present();
    }
    return 0;
}