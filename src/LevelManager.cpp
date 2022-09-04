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
#include "EntityComponents/Rendering/RepeatingTexture.h"
LevelManager::LevelManager(entt::registry* registry) : registry(registry){

}

void LevelManager::load_level_one(){
    reset();
    entt::entity player = registry -> create();
    SDL_Rect player_dimensions = {10, 10, 40, 40}; 
    registry -> emplace<Transform>(player, player_dimensions, true, 255, 0, 0, 255);
    registry -> emplace<PlayerController>(player);
    SDL_Texture* player_texture = TextureManager::load_image("assets/player.png");
    SDL_Rect player_texture_source_rect = {0, 0, 32, 32};
    registry -> emplace<Texture>(player, player_texture, player_texture_source_rect);
    registry -> emplace<Animations>(player, 32, 32, 4);
    registry -> emplace<Hitbox>(player, true);
    registry -> emplace<Core>(player);
    registry -> emplace<Movement>(player);    
    entt::entity ground = registry -> create();
    SDL_Rect ground_dimensions = {-1000, 900, 4000, 32};
    registry->emplace<Transform>(ground, ground_dimensions, true, 29, 161, 0, 255);
    registry->emplace<Hitbox>(ground);
    SDL_Texture* grass_texture = TextureManager::load_image("assets/grass.png");
    SDL_Rect grass_texture_source_rect = {0, 0, 32, 32};
    registry->emplace<Texture>(ground, grass_texture, grass_texture_source_rect);
    registry->emplace<RepeatingTexture>(ground);
}

void LevelManager::reset(){
    registry -> clear();
}