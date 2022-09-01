#include "TextureManager.hpp"

SDL_Window* TextureManager::window = nullptr;
SDL_Renderer* TextureManager::renderer = nullptr;
std::map<int, TTF_Font*> TextureManager::fonts_cache;