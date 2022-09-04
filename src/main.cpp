#include "TextureManager.hpp"
#include "ECSManager.hpp"
#include "LevelManager.hpp"
#include "OnScreenDebugger.hpp"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    TextureManager::init_windowing("test", 1000, 1000);
    bool quit = false;
    ECSManager ecs_manager;
    LevelManager level_manager(&ecs_manager.registry);
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    Uint32 frame_start;
    int frame_time;
    level_manager.load_level_one();


    while(!quit){
        frame_start = SDL_GetTicks();
        SDL_Event event;
        SDL_PumpEvents(); //this line should be removed normally, but events dont work for some reason when removed
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_F3:
                if(OnScreenDebugger::enabled){
                    OnScreenDebugger::enabled = false;
                }
                else{
                    OnScreenDebugger::enabled = true;
                }
                break;
            
            default:
                break;
            }
            break;
        default:
            break;
        }
        OnScreenDebugger::refresh();
        TextureManager::clear(112, 153, 255, 255);
        ecs_manager.update();
        OnScreenDebugger::draw();
        frame_time = SDL_GetTicks() - frame_start;
        if(frame_delay > frame_time){
            int fps = 1000.0 / (double) frame_delay - frame_time;
            std::string fps_char = std::to_string(fps);
            OnScreenDebugger::print("FPS: ");
            OnScreenDebugger::print(fps_char.c_str(), false);
            SDL_Delay(frame_delay - frame_time);
        }
        OnScreenDebugger::draw();
        TextureManager::present();
    }
    return 0;
}

