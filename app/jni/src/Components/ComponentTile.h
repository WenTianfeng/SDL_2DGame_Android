#ifndef COMPONENT_TILE
#define COMPONENT_TILE

#include"../HeaderFiles/Game.h"
#include"../../UtilLib/glm/glm.hpp"
#include"ComponentTransform.h"
#include"../HeaderFiles/TextureManager.h"

class ComponentTile :public Component {
public:
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    glm::vec2 position;
    ComponentTransform* transform;

    ComponentTile(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId) {
        texture = Game::getInstance()->assetManager->GetTexture(assetTextureId);
        

        sourceRect.x = sourceRectX;
        sourceRect.y = sourceRectY;
        sourceRect.w = tileSize;
        sourceRect.h = tileSize;

        destRect.x = x;
        destRect.y = y;
        destRect.w = tileSize * tileScale;
        destRect.h = tileSize * tileScale;

        position.x = x;
        position.y = y;
    }

    ~ComponentTile(){
        SDL_DestroyTexture(texture);
    }

    void Initialize() override {
        transform = owner->GetComponent<ComponentTransform>();
    
    }

    void Update(float deltaTime) override {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void Render(float offsetX,float offsetY) override {
        SDL_Rect offsetRect={static_cast<int>(destRect.x-offsetX),static_cast<int>(destRect.y-offsetY),destRect.w,destRect.h};
        TextureManager::DrawTexture(texture, sourceRect, offsetRect, SDL_FLIP_NONE);
    }


};



#endif // !COMPONENT_TILE

