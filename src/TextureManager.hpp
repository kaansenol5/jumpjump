/*  17/6/2022
    universal class for every game ever.
    it must be one single header
    it must not depend on anything other than sdl.
*/
#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include "OnScreenDebugger.hpp"
/* 
ALL OF THE FUNCTIONS ASSUMES THAT SDL_Init(), TTF_Init() and IMG_Init were called earlier
*/


class TextureManager{
public:
    static inline int init_windowing(char* title, int width, int height){
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
        if (window == NULL){
            return 1;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        if (renderer == NULL){
            return 1;
        }
        return 0;
    }

    static inline SDL_Texture* load_image(const char* file){
        SDL_Surface* temp_surface = IMG_Load(file);
        if(!temp_surface){
            std::cout << "IMG_Load(" << file << ") call has returned nullptr. Error Code: "  << IMG_GetError() << std::endl;
         }      
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
        if (!texture){
            std::cout << "Texture loaded by TextureManager::load_image() may be invalid, image file name: " << file << std::endl;
            std::cout << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(temp_surface);
        return texture;
    }

    static inline SDL_Texture* load_ttf_font(const char* font_file, const char* text, const int ptsize, const SDL_Color color){
        if (fonts_cache.find(ptsize) != fonts_cache.end())
            {
                // Font not yet opened. Open and store it.
                fonts_cache[ptsize] = TTF_OpenFont(font_file,ptsize);
                // TODO: error checking...
            }
        if(!fonts_cache[ptsize]){
            std::cout << "Failed loading font by TextureManager::load_ttf_font() , font file name: " << font_file << std::endl;
            std::cout << "Error Code: " << TTF_GetError() << std::endl;
        }
        SDL_Surface* temp_surface = TTF_RenderText_Solid(fonts_cache[ptsize], text, color);
        if(!temp_surface){
            std::cout << "TTF_RenderText_Solid() failed, Error Code: " << SDL_GetError() << std::endl;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);        
        if (!texture){
            std::cout << "Texture generation failed at TextureManager::load_ttf_font() " << font_file << std::endl;
            std::cout << "Error Code: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(temp_surface);
        return texture;
    }

    static inline bool check_bounds(SDL_Rect* dest){
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        if(dest->x >= 0 && dest->x <= width && dest->y >= 0 && dest->y <= height){
            return true;
        }
        else{
            return false;
        }
    }

    static inline void render(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest){
        if(check_bounds(dest)){ //check if destination rect is in the screen
            if(SDL_RenderCopy(renderer, texture, source, dest) != 0){
                std::cout << "Failed rendering!!: " << SDL_GetError() << " at x:" <<  dest->x << ", y: "  << dest->y << std::endl;
              //  std::cout << "Texture: " << texture << std::endl;
            }
        }
    }

    static inline void draw_rect(SDL_Rect *dest, SDL_Color color, bool filled){
        if(check_bounds(dest)){
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            if(filled){
                if(SDL_RenderFillRect(renderer, dest) != 0){
                    std::cout << "SDL_RenderFillRect() failed! Error Code: " << SDL_GetError() << std::endl;
                };
            }
            else{
                if(SDL_RenderDrawRect(renderer, dest) != 0){
                    std::cout << "SDL_DrawRect() failed! Error Code: " << SDL_GetError() << std::endl;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        }
  }

  static inline void clear(unsigned char r = 0, unsigned char b = 0, unsigned char g = 0, unsigned char a = 255){
      SDL_SetRenderDrawColor(renderer, r, g, b, a);
      SDL_RenderClear(renderer);
  }

  static inline void present(){
      SDL_RenderPresent(renderer);
  }
private:
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static std::map<int, TTF_Font*> fonts_cache;
};