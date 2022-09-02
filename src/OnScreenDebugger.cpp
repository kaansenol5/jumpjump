#include "OnScreenDebugger.hpp"
#include "TextureManager.hpp"

char* OnScreenDebugger::fontname = "assets/font.ttf";
int OnScreenDebugger::ptsize = 14;
SDL_Color OnScreenDebugger::color = {255,255,255,150};
std::vector<std::string> OnScreenDebugger::screen;
bool OnScreenDebugger::enabled = true;


void OnScreenDebugger::refresh(){
    screen = {""};
}

void OnScreenDebugger::print(std::string text, bool newline){
    if(newline){
        screen.push_back(text);
    }
    else{
        screen.back().append(text);
    }
}

void OnScreenDebugger::draw(){
    if(!enabled){
        return;
    }
    int size = screen.size();
    for(int i = 0; i < size; i++){
        std::string& line = screen[i]; 
        SDL_Rect rect = {10, i* ptsize, ptsize * line.size(), ptsize};
        SDL_Texture* texture = TextureManager::load_ttf_font(fontname, line.c_str(), 128, color);
        TextureManager::render(texture, nullptr, &rect);
    }
}