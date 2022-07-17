//necessary component for most physics function
struct Core
{
    bool gravity = true;
    float mass = 10.0f;
    float max_force = 2.0f; 
    float total_force_x = .0f;
    float total_force_y = .0f;
};
