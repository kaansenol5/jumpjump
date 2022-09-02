#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
// avaliable: ~, blocked: |

class OnScreenDebugger{
public:
    static void refresh();
    static void print(std::string text, bool newline = true);
    static void draw();
    static bool enabled;
private:
    static char* fontname;
    static int ptsize;
    static std::vector<std::string> screen;
    static SDL_Color color;
};