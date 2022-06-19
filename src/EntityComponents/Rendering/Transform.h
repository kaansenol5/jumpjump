#pragma once
#include <SDL2/SDL.h>

struct Transform{
    SDL_Rect rect = {0, 0, 0, 0};
    bool filled_rect = true;
    SDL_Color rect_color = {255, 255, 255, 255};
};