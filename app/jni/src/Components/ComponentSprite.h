#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H


#include"../HeaderFiles/Game.h"
#include"ComponentTransform.h"
#include"../HeaderFiles/AssetManager.h"
#include"../HeaderFiles/Animation.h"
#include "./HeaderFiles/Interfaces.h"


/*
精灵显示组件
继承自组件基类和轮盘可控接口
*/
class ComponentSprite:public Component,public IControlledByJoystick{
    private:
        ComponentTransform* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destRect;

        bool isAnimated;
        int numFrame;
        int animationSpeed;
        bool isFixed;

        std::map<std::string, Animation> animations;
        std::string currentAnimation;
        int animationIndex;


    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        ~ComponentSprite() {}

        ComponentSprite(std::string assetTextureID){

            SetTexture(assetTextureID);
            isAnimated = false;
        }


        ComponentSprite(std::string assetTextureID,int numFrame,int animationSpeed,bool hasDirection,bool isFixed) {
            SetTexture(assetTextureID);

            isAnimated = true;
            this->numFrame = numFrame;
            this->isFixed = isFixed;
            this->animationSpeed = animationSpeed;

            if (hasDirection) {
                Animation animationDown = Animation(0, numFrame, animationSpeed);
                Animation animationRight = Animation(1, numFrame, animationSpeed);
                Animation animationLeft = Animation(2, numFrame, animationSpeed);
                Animation animationUp = Animation(3, numFrame, animationSpeed);

                animations.emplace("AnimationDown", animationDown);
                animations.emplace("AnimationRight", animationRight);
                animations.emplace("AnimationLeft", animationLeft);
                animations.emplace("AnimationUp", animationUp);

                this->animationIndex = 0;
                this->currentAnimation = "AnimationDown";

            }
            else {
                Animation singleAnimation = Animation(0, numFrame, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                this->animationIndex = 0;
                this->currentAnimation = "SingleAnimation";
            }

            PlayAnimation(this->currentAnimation);

        
        }

        void PlayAnimation(std::string animationName) {
            numFrame = animations[animationName].numFrame;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimation = animationName;

        }

        void SetTexture(std::string assetTextureID){
            texture = Game::getInstance()->assetManager->GetTexture(assetTextureID);
     
        }

        void Initialize() override{

            

            transform = owner->GetComponent<ComponentTransform>();
            sourceRect.x = 0;
            sourceRect.y = 0;
            //待修改/////////////////////////////////////
            sourceRect.w = 32;
            sourceRect.h = 32;
        
        }


        void Update(float deltaTime) override {
            if (isAnimated) {
                sourceRect.x = sourceRect.w * (static_cast<int>(SDL_GetTicks() / animationSpeed) % numFrame);
                sourceRect.y = sourceRect.h * animationIndex;
            }

            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = transform->width*transform->scale;
            destRect.h = transform->height*transform->scale;
          
          
        }

        void Render(float offsetX,float offsetY) override {
            SDL_Rect offsetRect={static_cast<int>(destRect.x-offsetX),static_cast<int>(destRect.y-offsetY),destRect.w,destRect.h};
            TextureManager::DrawTexture(texture,sourceRect,offsetRect,spriteFlip);
  
        }


    //=================IControlledByJoystick接口实现===================

        void UpdateByJoystick(glm::vec2 normalizedDir) override{

            if (glm::abs(normalizedDir.x) > glm::abs(normalizedDir.y)) {
                if (normalizedDir.x > 0) {
                    PlayAnimation("AnimationRight");
                }
                else {
                    PlayAnimation("AnimationLeft");
                }
            }
            else {
                if (normalizedDir.y > 0) {
                    PlayAnimation("AnimationDown");
                }
                else {
                    PlayAnimation("AnimationUp");
                }
            }

        }

        virtual void OnJoystickInvalid() override{
        }

};


#endif