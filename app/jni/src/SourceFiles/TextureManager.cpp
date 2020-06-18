#include"../HeaderFiles/TextureManager.h"

/*
 * Texture加载控制
 * */


//加载Texture
//param:filePath 文件路径
//return：SDL_Texture对象
SDL_Texture* TextureManager::LoadTexture(const char* filePath){
    SDL_Surface* surface = IMG_Load(filePath);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer,surface);
    SDL_FreeSurface(surface);
    return texture;

}


//绘制Texture
void TextureManager::DrawTexture(SDL_Texture* texture,SDL_Rect sourceRect,SDL_Rect destRect,SDL_RendererFlip flip){
    SDL_RenderCopyEx(Game::renderer,texture,&sourceRect,&destRect,0.0,NULL,flip);

}