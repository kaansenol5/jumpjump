#pragma once
#include <SDL2/SDL_ttf.h>

// avaliable: ~, blocked: |

class OnScreenDebugger{
public:
    static void refresh();
    static void print(char* text, bool newline = true);
    static void draw();
private:
    static char* fontname;
    static int ptsize;
    static char screen[80][80];
    static SDL_Color color;
};