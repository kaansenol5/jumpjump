#include "include/entt.hpp"

class LevelManager{
public:
    LevelManager(entt::registry* registry);
    void load_level_one();
private:
    void reset();
    entt::registry* registry;
};