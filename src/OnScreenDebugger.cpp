#include "OnScreenDebugger.hpp"
#include "TextureManager.hpp"

OnScreenDebugger::OnScreenDebugger(){
    refresh();
}

void OnScreenDebugger::refresh(){
    for(unsigned i = 0; i < 80; i++){
        for(unsigned j = 0; j < 80; j++){
            screen[i][j] = '~';
        }
    }
}

void OnScreenDebugger::print(char* text, bool newline){
    int current_char = 0;
    for(unsigned i = 0; i < 80; i++){
        for(unsigned j = 0; j < 80; j++){
            if(screen[i][j] == '~'){
                if(current_char == strlen(text) - 1){
                    if(newline){
                        screen[i][j] = '|';
                    }
                }
                else{
                    screen[i][j] = text[current_char];
                    current_char++;
                }
            }
        }
    }
}

void OnScreenDebugger::draw(){
    for(int i = 0; i < 80; i++){
        for(int j = 0; j < 80; j++){
            if(screen[i][j] != '~' && screen[i][j] != '|'){
                SDL_Rect rect = {i * 100, j * 100, 100, 100};
                SDL_Texture* text = TextureManager::load_ttf_font(fontname, &screen[i][j], ptsize, color);
                TextureManager::render(text, nullptr, &rect);
            }
        }
    }
}