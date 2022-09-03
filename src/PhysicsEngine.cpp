#include "PhysicsEngine.hpp"
#include "EntityComponents/Physics/Hitbox.h"
#include "EntityComponents/Physics/Core.h"
#include "EntityComponents/Rendering/Transform.h"
#include "EntityComponents/Physics/Movement.h"
#include "OnScreenDebugger.hpp"
#include <iostream>

PhysicsEngine::PhysicsEngine(entt::registry& registry) : registry(registry){}

void PhysicsEngine::update_movements(){
    registry.view<Core, Movement, Transform>().each([this](entt::entity entity, Core& core, Movement& movement, Transform& transform){
        if(core.gravity){
            if(core.total_force_y < core.max_force){
                core.total_force_y += core.mass * core.gravity;
            }
        }
        movement.acceleration_x = core.total_force_x / core.mass;
        movement.acceleration_y = core.total_force_y / core.mass;
        OnScreenDebugger::print("force_y: " + std::to_string(core.total_force_y));
        OnScreenDebugger::print("vel_y: " + std::to_string(movement.velocity_y));
        if(abs(movement.velocity_x + movement.acceleration_x) <= movement.max_velocity){
            movement.velocity_x += movement.acceleration_x;
        }
        if(abs(movement.velocity_y + movement.acceleration_y) <= movement.max_velocity){
            movement.velocity_y += movement.acceleration_y;
        }
        if(movement.velocity_x != 0){
            if(movement.velocity_x < 0){
                movement.velocity_x += friction;
            }
            else{
                movement.velocity_x -= friction;
            }
        }
        if(movement.velocity_y != 0){

            if(movement.velocity_y < 0){
                movement.velocity_y += friction;
            }
            else{
                movement.velocity_y -= friction;
            }
        }
        if(core.total_force_x != 0){
            if(core.total_force_x < 0){
                core.total_force_x += friction;
            }
            else{
                core.total_force_x -= friction;
            }
        }
        if(core.total_force_y != 0){
            if(core.total_force_y < 0){
                core.total_force_y += friction;
            }
            else{
                core.total_force_y -= friction;
            }
        }
        move(entity, 0, movement.velocity_y);
        move(entity, movement.velocity_x, 0);
    });
    
}

void PhysicsEngine::add_force(entt::entity entity, int xd, int yd){
    Core& core = registry.get<Core>(entity);
    if(abs(core.total_force_x + xd) <= core.max_force){
        core.total_force_x += xd;
    }
    if(abs(core.total_force_y + yd) <= core.max_force){
        core.total_force_y += yd;
    }
}

void PhysicsEngine::move(entt::entity entity, int xd, int yd){ 
    Transform& transform = registry.get<Transform>(entity);
    Hitbox* hitbox = registry.try_get<Hitbox>(entity);
    Transform new_transform = transform;
    new_transform.rect.x += xd;
    new_transform.rect.y += yd;
    if(hitbox == nullptr){
        transform = new_transform;
    }

    else{
        bool col = false;
        registry.view<Transform, Hitbox>().each([entity, new_transform, &col, this](entt::entity e2, Transform& t2, Hitbox& h2){
            if(entity != e2){
                if(new_transform.rect.x +  new_transform.rect.w > t2.rect.x && new_transform.rect.x < t2.rect.x + t2.rect.w){
                    if(new_transform.rect.y +  new_transform.rect.h > t2.rect.y && new_transform.rect.y < t2.rect.y + t2.rect.h){
                        col = true;
                        OnScreenDebugger::print("COLLISION");
                        Movement* movement = registry.try_get<Movement>(entity);
                        if(movement != nullptr){
                            movement->velocity_x / 2;
                            movement->velocity_y / 2;
                        }
                    }
                }
            }
        });
        if(!col){
            transform = new_transform;
        }        
    }
}

