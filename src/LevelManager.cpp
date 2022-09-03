#include "LevelManager.hpp"
#include "SDL2/SDL.h"
#include "TextureManager.hpp"
#include "EntityComponents/Controllers/PlayerController.h"
#include "EntityComponents/Rendering/Texture.h"
#include "EntityComponents/Rendering/Animations.h"
#include "EntityComponents/Rendering/Transform.h"
#include "EntityComponents/Physics/Core.h"
#include "EntityComponents/Physics/Movement.h"
#include "EntityComponents/Physics/Hitbox.h"

LevelManager::LevelManager(entt::registry* registry) : registry(registry){

}

void LevelManager::load_level_one(){
    reset();
    entt::entity player = registry -> create();
    SDL_Rect player_dimensions = {10, 10, 40, 40}; 
    registry -> emplace<Transform>(player, player_dimensions, true, 255, 0, 0, 255);
    registry -> emplace<PlayerController>(player);
    SDL_Texture* texture = TextureManager::load_image("assets/player.png");
    SDL_Rect texture_source_rect = {0, 0, 32, 32};
   // registry -> emplace<Texture>(player, texture, texture_source_rect);
   // registry -> emplace<Animations>(player, 32, 32, 4);
    registry -> emplace<Hitbox>(player, true);
    registry -> emplace<Core>(player);
    registry -> emplace<Movement>(player);
    
    entt::entity box = registry -> create();
    SDL_Rect box_dimensions = {0, 900, 4000, 10};
    registry->emplace<Transform>(box, box_dimensions);
    registry->emplace<Hitbox>(box, false);
}

void LevelManager::reset(){
    registry -> clear();
}