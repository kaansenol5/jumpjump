#pragma once
#include <SDL2/SDL_ttf.h>

// avaliable: ~, blocked: |

class OnScreenDebugger{
public:
    OnScreenDebugger();
    void refresh();
    void print(char* text, bool newline = true);
    void draw();
private:
    char* fontname = "assets/font.ttf";
    int ptsize = 8;
    char screen[80][80];
    SDL_Color color = {255,255,255,255};
};