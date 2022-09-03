#include "include/entt.hpp"
#include "EntityComponents/Rendering/Transform.h"

class PhysicsEngine{
public:
    PhysicsEngine(entt::registry& registry);
    void update_movements();
    void add_force(entt::entity entity, int xd, int yd);
private:
    void move(entt::entity entity, int xd, int yd);
    int gravity = 1;
    float friction = .5f;
    entt::registry& registry;};