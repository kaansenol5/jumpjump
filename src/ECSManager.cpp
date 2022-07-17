#include "ECSManager.hpp"
#include "EntityComponents/Rendering/Texture.h"
#include "EntityComponents/Rendering/Transform.h"
#include "EntityComponents/Rendering/Animations.h"
#include "EntityComponents/Controllers/PlayerController.h"
#include "EntityComponents/Physics/Hitbox.h"
#include "TextureManager.hpp"

ECSManager::ECSManager() : physics(registry){}

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
        if (keys[SDL_SCANCODE_SPACE] && !controller.is_jumping){
            controller.is_jumping = true;
        }
        if (controller.is_jumping){
            unsigned jumphalf = controller.jump_lenght / 2;
            if (controller.jumped_lenght < jumphalf){
                controller.jumped_lenght++;
                physics.move(entity, 0, controller.force * -1);
            }
            else{
                controller.jumped_lenght++;
                physics.move(entity, 0, controller.force * 1);
            }
            if (controller.jumped_lenght >= controller.jump_lenght){
                controller.is_jumping = false;
                controller.jumped_lenght = 0;
            }
        }
        
    });
    physics.update_movements();
}
