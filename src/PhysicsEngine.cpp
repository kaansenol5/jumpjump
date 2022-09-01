#include "PhysicsEngine.hpp"
#include "EntityComponents/Physics/Hitbox.h"
#include "EntityComponents/Physics/Core.h"
#include "EntityComponents/Rendering/Transform.h"
#include "EntityComponents/Physics/Movement.h"
PhysicsEngine::PhysicsEngine(entt::registry& registry) : registry(registry){}

void PhysicsEngine::update_movements(){
    registry.view<Core, Movement, Transform>().each([this](entt::entity entity, Core& core, Movement& movement, Transform& transform){
        if(core.gravity){
          //  core.total_force_y += core.mass * gravity;
        }
        movement.acceleration_x = core.total_force_x / core.mass;
        movement.acceleration_y = core.total_force_y / core.mass;
        if(abs(movement.velocity_x + movement.acceleration_x) <= movement.max_velocity){
            movement.velocity_x += movement.acceleration_x;
        }
        if(abs(movement.velocity_y + movement.acceleration_y) <= movement.max_velocity){
            movement.velocity_y += movement.acceleration_y;
        }
        if(movement.velocity_x != 0){
            //float u = 
           // float friction = u * abs(core.total_force_x);
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
        move(entity, movement.velocity_x, movement.velocity_y);
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

bool PhysicsEngine::update_collision(){
    // this gets executed multiple times per frame
    // this gets executed after every move call, for example
    bool collide = false;
    registry.view<Hitbox>().each([this, &collide](auto entity1, Hitbox& h1){
        registry.view<Hitbox>().each([this, &collide, entity1](auto entity2, Hitbox& h2){
            if (entity1 != entity2){
                collide = check_collision(entity1, entity2);
            }
        });
    });
    return collide;
}
void PhysicsEngine::move(entt::entity entity, int xd, int yd){
    Transform& transform = registry.get<Transform>(entity);
    Transform old_transform = transform;
    transform.rect.x += xd;
    transform.rect.y += yd;
    bool collision_result = update_collision();
    if (collision_result){
        transform = old_transform; // undo the movement if movement results in collision 
    }
}




bool PhysicsEngine::check_collision(entt::entity e1, entt::entity e2){
    Transform& t1 = registry.get<Transform>(e1);
    Transform& t2 = registry.get<Transform>(e2);
    if((t1.rect.x + t1.rect.w > t2.rect.x) && (t1.rect.x < t2.rect.x + t2.rect.w)){
        if((t1.rect.y + t1.rect.h > t2.rect.y) && (t1.rect.y < t2.rect.y + t2.rect.h)){
            return true;
        }
    }
    return false;
}

