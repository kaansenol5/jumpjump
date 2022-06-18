#include <SDL2/SDL.h>

class Transform{
public:
    void draw();
private:
    SDL_Rect rect = {0, 0, 0, 0};
};