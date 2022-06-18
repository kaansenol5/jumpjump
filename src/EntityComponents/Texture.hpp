#include <SDL2/SDL.h>

class Texture{
public:
    inline void draw(){
        
    }
private:
    SDL_Texture* texture = nullptr;
    SDL_Rect source_rect = {0, 0, 0, 0};
};