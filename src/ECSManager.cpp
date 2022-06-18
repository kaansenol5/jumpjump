#include "ECSManager.hpp"
#include "EntityComponents/Texture.h"
#include "EntityComponents/Transform.h"
#include "EntityComponents/Animations.h"
#include "EntityComponents/PlayerController.h"
#include "EntityComponents/Hitbox.h"
#include "TextureManager.hpp"

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
    
    registry.view<Transform, Texture>().each([](auto entity, Transform& transform, Texture& texture){
        TextureManager::render(texture.texture, &texture.source_rect, &transform.rect);
    });

    registry.view<Hitbox, Transform>().each([this](auto entity, Hitbox& hitbox, Transform& transform){
        Hitbox& current_hitbox = hitbox;
        current_hitbox.is_colliding = false;
        Transform& current_transform = transform;
        registry.view<Hitbox, Transform>().each([&current_hitbox, &current_transform](auto entity, Hitbox& hitbox, Transform& transform){
            if(&hitbox != &current_hitbox && &transform != &current_transform){
                if(current_transform.rect.x + current_transform.rect.w >= transform.rect.x && current_transform.rect.x + current_transform.rect.w <= transform.rect.x + transform.rect.w){
                    current_hitbox.is_colliding = true;
                }
                if(current_transform.rect.y + current_transform.rect.h >= transform.rect.y && current_transform.rect.y + current_transform.rect.h <= transform.rect.y + transform.rect.h){
                    current_hitbox.is_colliding = true;
                }
            }
    });});

    registry.view<PlayerController, Transform>().each([this](auto entity, PlayerController& controller, Transform& transform){
        Hitbox& player_hitbox = registry.get<Hitbox>(entity);
        
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]){
            transform.rect.y -= controller.velocity;
        }
        if (keys[SDL_SCANCODE_S]){
            transform.rect.y += controller.velocity;
        }
        if (keys[SDL_SCANCODE_A]){
            transform.rect.x -= controller.velocity;
        }
        if (keys[SDL_SCANCODE_D]){
            transform.rect.x += controller.velocity;
        }
        if (keys[SDL_SCANCODE_SPACE] && !controller.is_jumping){
            controller.is_jumping = true;
        }
        if (controller.is_jumping){
            unsigned jumphalf = controller.jump_lenght / 2;
            if (controller.jumped_lenght < jumphalf){
                controller.jumped_lenght++;
                transform.rect.y -= controller.velocity;
            }
            else{
                controller.jumped_lenght++;
                transform.rect.y += controller.velocity;
            }
            if (controller.jumped_lenght >= controller.jump_lenght){
                controller.is_jumping = false;
                controller.jumped_lenght = 0;
            }
        }
    });

}