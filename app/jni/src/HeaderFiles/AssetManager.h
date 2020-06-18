#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include<map>
#include<string>
#include"TextureManager.h"
#include"FontManager.h"


/*
 *资源控制类
*/
class AssetManager{
    private:
        std::map<std::string,SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
    public:
        AssetManager();
        ~AssetManager();
        void ClearData();
        void AddTexture(std::string textureID,const char* filePath);    //添加Texture资源
        void AddFont(std::string fontID, const char* filePath, int fontSize);   //添加Font资源
        
        SDL_Texture* GetTexture(std::string textureID); //获取Texture对象
        TTF_Font* GetFont(std::string fontID);  //获取Font对象


};



#endif