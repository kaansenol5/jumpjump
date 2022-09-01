#include "include/entt.hpp"


class PhysicsEngine{
public:
    PhysicsEngine(entt::registry& registry);
    void update_movements();
    void add_force(entt::entity entity, int xd, int yd);

    void move(entt::entity entity, int xd, int yd);
private:
    int gravity = 1;
    float friction = .5f;
    entt::registry& registry;
    bool update_collision(); // this checks if t collides with every other hitbox in game and uses the check_collision() method below
    bool check_collision(entt::entity e1, entt::entity e2); // this checks if t1 and t2 transforms collide
};