#include "ECSManager.hpp"
#include "EntityComponents/Texture.h"
#include "EntityComponents/Transform.h"
#include "EntityComponents/Animations.h"
#include "EntityComponents/PlayerController.h"
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

    registry.view<PlayerController, Transform>().each([](auto entity, PlayerController& controller, Transform& transform){
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