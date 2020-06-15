#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include<map>
#include<string>
#include"TextureManager.h"
#include"FontManager.h"



class AssetManager{
    private:
        std::map<std::string,SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
    public:
        AssetManager();
        ~AssetManager();
        void ClearData();
        void AddTexture(std::string textureID,const char* filePath);
        void AddFont(std::string fontID, const char* filePath, int fontSize);
        
        SDL_Texture* GetTexture(std::string textureID);
        TTF_Font* GetFont(std::string fontID);


};



#endif