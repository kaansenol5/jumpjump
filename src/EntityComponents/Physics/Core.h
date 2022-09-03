//necessary component for most physics function
struct Core
{
    bool gravity = true;
    float mass = 4.0f;
    float max_force = 5.0f; 
    float total_force_x = .0f;
    float total_force_y = .0f;
};
