#include "include/entt.hpp"
#include "PhysicsEngine.hpp"

class ECSManager{
public:
    ECSManager();
    void update();
    entt::registry registry;
    PhysicsEngine physics;
};