#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL.h"
#include "SDL_image.h"

class TextureManager{
    public:
        static SDL_Texture* LoadTexture(const char* filePath);
        static void DrawTexture(SDL_Texture*texture,SDL_Rect sourceRect,SDL_Rect destRect,SDL_RendererFlip flip);




};




#endif