#include "TextureManager.hpp"
#include "ECSManager.hpp"
#include "EntityComponents/Rendering/Transform.h"
#include "EntityComponents/Rendering/Texture.h"
#include "EntityComponents/Rendering/Animations.h"
#include "EntityComponents/Controllers/PlayerController.h"
#include "EntityComponents/Physics/Hitbox.h"
#include "EntityComponents/Physics/Core.h"
#include "EntityComponents/Physics/Movement.h"
#include "OnScreenDebugger.hpp"
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
    entt::entity player = ecs_manager.registry.create();
    SDL_Rect player_dimensions = {10, 10, 40, 40}; 
    ecs_manager.registry.emplace<Transform>(player, player_dimensions, true, 255, 0, 0, 255);
    ecs_manager.registry.emplace<PlayerController>(player);
    SDL_Texture* texture = TextureManager::load_image("assets/player.png");
    SDL_Rect texture_source_rect = {0, 0, 32, 32};
  //  ecs_manager.registry.emplace<Texture>(player, texture, texture_source_rect);
    //ecs_manager.registry.emplace<Animations>(player, 32, 32, 4);
    ecs_manager.registry.emplace<Hitbox>(player, true);
    ecs_manager.registry.emplace<Core>(player);
    ecs_manager.registry.emplace<Movement>(player);


    while(!quit){
        frame_start = SDL_GetTicks();
        SDL_Event event;
        SDL_PumpEvents(); //this line should be removed normally, but events dont work for some reason when removed
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_F3:
                if(OnScreenDebugger::enabled){
                    OnScreenDebugger::enabled = false;
                }
                else{
                    OnScreenDebugger::enabled = true;
                }
                break;
            
            default:
                break;
            }
            break;
        default:
            break;
        }
        OnScreenDebugger::refresh();
        TextureManager::clear(0, 255, 0, 255);
        ecs_manager.update();
        OnScreenDebugger::print("HELLO ", false);
        OnScreenDebugger::print("WORLD");
        OnScreenDebugger::print("nice");
        OnScreenDebugger::draw();
        TextureManager::present();
        frame_time = SDL_GetTicks() - frame_start;
        if(frame_delay > frame_time){
            SDL_Delay(frame_delay - frame_time);
        }
    }
    return 0;
}

