#include <SDL2/SDL.h>

struct Texture{
    SDL_Texture* texture = nullptr;
    SDL_Rect source_rect = {0, 0, 0, 0};
};