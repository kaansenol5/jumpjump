#include "OnScreenDebugger.hpp"
#include "TextureManager.hpp"

char* OnScreenDebugger::fontname = "assets/font.ttf";
int OnScreenDebugger::ptsize = 24;
SDL_Color OnScreenDebugger::color = {255,255,255,150};
char OnScreenDebugger::screen[80][80];
bool OnScreenDebugger::enabled = true;


void OnScreenDebugger::refresh(){
    for(unsigned i = 0; i < 80; i++){
        for(unsigned j = 0; j < 80; j++){
            screen[i][j] = '~';
        }
    }
}

void OnScreenDebugger::print(const char* text, bool newline){
    int current_char = 0;
    for(unsigned i = 0; i < 80; i++){
        for(unsigned j = 0; j < 80; j++){
            if(screen[i][j] == '~'){
                if(current_char == strlen(text)){
                    if(newline){
                        for(int a = j; a<80; a++){
                            screen[i][a] = '|';
                        }
                    }
                    return;
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
                SDL_Rect rect = {j * ptsize, i * ptsize, ptsize, ptsize};
                char txt[2];  // WTF IS THIS
                txt[0] = screen[i][j];  
                SDL_Texture* text = TextureManager::load_ttf_font(fontname, txt, ptsize, color);
                if(enabled)
                    TextureManager::render(text, nullptr, &rect);
            }
        }
    }
}