#include "TextureManager.hpp"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    TextureManager::init_windowing("test", 100, 100);
    return 0;
}