#include "include/entt.hpp"
#include "EntityComponents/Rendering/Transform.h"

class PhysicsEngine{
public:
    PhysicsEngine(entt::registry& registry);
    void update_movements();
    void add_force(entt::entity entity, int xd, int yd, bool ignore_limit = false);
private:
    void move(entt::entity entity, int xd, int yd);
    bool check_col(entt::entity entity, Transform new_transform);
    int gravity = 1;
    float friction = .5f;
    entt::registry& registry;};