#include "PhysicsEngine.hpp"
#include "EntityComponents/Physics/Hitbox.h"
#include "EntityComponents/Rendering/Transform.h"

PhysicsEngine::PhysicsEngine(entt::registry& registry) : registry(registry){}

void PhysicsEngine::update_gravity(){

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

