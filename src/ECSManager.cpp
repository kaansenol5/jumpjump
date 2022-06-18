#include "ECSManager.hpp"
#include "EntityComponents/Texture.h"
#include "EntityComponents/Transform.h"
#include "TextureManager.hpp"

void ECSManager::update(){
    registry.view<Transform>(entt::exclude<Texture>).each([](auto entity, Transform& transform){
        TextureManager::draw_rect(&transform.rect, transform.rect_color, transform.filled_rect);
    });
    
    registry.view<Transform, Texture>().each([](auto entity, Transform& transform, Texture& texture){
        TextureManager::render(texture.texture, &texture.source_rect, &transform.rect);
    });
}