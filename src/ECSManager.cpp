#include "ECSManager.hpp"
#include "EntityComponents/Rendering/Texture.h"
#include "EntityComponents/Rendering/Transform.h"
#include "EntityComponents/Rendering/Animations.h"
#include "EntityComponents/Rendering/RepeatingTexture.h"
#include "EntityComponents/Controllers/PlayerController.h"
#include "EntityComponents/Physics/Hitbox.h"
#include "EntityComponents/Physics/Movement.h"
#include "TextureManager.hpp"

ECSManager::ECSManager() : physics(registry){
    //registry.on_construct<Hitbox>().connect<&entt::registry::emplace_or_replace<Movement>>();
}

void ECSManager::update(){
    registry.view<Transform>(entt::exclude<Texture>).each([](auto entity, Transform& transform){
        TextureManager::draw_rect(&transform.rect, transform.rect_color, transform.filled_rect);
    });

    registry.view<Animations, Texture>().each([](auto entity, Animations& animations, Texture& texture){
        int sprite_w, sprite_h, sprite_x, sprite_y;
        sprite_x = animations.single_sprite_width * animations.current_sprite;
        sprite_y = 0;
        sprite_w = animations.single_sprite_width;
        sprite_h = animations.single_sprite_height;
        texture.source_rect = {sprite_x, sprite_y, sprite_w, sprite_h};
        animations.current_sprite++;
        if (animations.current_sprite > animations.sprites_amount){
            animations.current_sprite = 0;
        }
    });
    
    registry.view<Transform, Texture>(entt::exclude<RepeatingTexture>).each([](auto entity, Transform& transform, Texture& texture){
        TextureManager::render(texture.texture, &texture.source_rect, &transform.rect);
    });
    registry.view<Transform, RepeatingTexture, Texture>().each([](auto entity, Transform& transform, RepeatingTexture& repeating_texture, Texture& texture){
        int width;
        int height;
        width = transform.rect.w / texture.source_rect.w;
        height = transform.rect.h / texture.source_rect.h;
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                SDL_Rect dest_rect = {i * texture.source_rect.w + transform.rect.x, j * texture.source_rect.h + transform.rect.y, texture.source_rect.w, texture.source_rect.h};
                TextureManager::render(texture.texture, &texture.source_rect, &dest_rect);
            }
        }
    });


    registry.view<PlayerController, Transform>().each([this](auto entity, PlayerController& controller, Transform& transform){
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]){
            physics.add_force(entity, 0, controller.force * -1);
        }
        if (keys[SDL_SCANCODE_S]){
            physics.add_force(entity, 0, controller.force * 1);
        }
        if (keys[SDL_SCANCODE_A]){
            physics.add_force(entity, controller.force * -1, 0);
        }
        if (keys[SDL_SCANCODE_D]){
            physics.add_force(entity, controller.force * 1, 0);
        }
        if (keys[SDL_SCANCODE_SPACE]){
            physics.jump(entity, -60);
        }
        
    });
    physics.update_movements();
}
