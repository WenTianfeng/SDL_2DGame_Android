#ifndef COMPONENT_BUTTON_H
#define COMPONENT_BUTTON_H

#include <list>
#include"../HeaderFiles/Game.h"
#include"../../UtilLib/glm/glm.hpp"
#include "./HeaderFiles/Interfaces.h"


class ComponentButton:public Component{

private:
    std::list<IControlledByButton*> controlledThings;//被该轮盘控制的物体

    SDL_Texture* buttonTexture;
    SDL_Texture* buttonNormalTexture;
    SDL_Texture* buttonPressedTexture;
    //滑动区域rect
    SDL_Rect buttonSourceRect;
    SDL_Rect buttonDestRect;

    bool isValidTouch;//目前是否处于触摸状态
    int m_fingerId = -1;


public:

    ComponentButton(std::string assetButtonNormalTextureID,std::string assetButtonPressedTextureID,int x,int y,int buttonWidth,int buttonHeight){

        buttonNormalTexture = Game::getInstance()->assetManager->GetTexture(assetButtonNormalTextureID);
        buttonPressedTexture = Game::getInstance()->assetManager->GetTexture(assetButtonPressedTextureID);
        buttonSourceRect.x = 0;
        buttonSourceRect.y = 0;
        buttonSourceRect.w = 32;
        buttonSourceRect.h = 32;
        buttonDestRect.w = buttonWidth;
        buttonDestRect.h = buttonHeight;
        buttonDestRect.x =x;
        buttonDestRect.y =y;

    }

    void Initialize() override {
        buttonTexture = buttonNormalTexture;
    }



    //根据输入状态得到输入结果，并改变button的显示
    void Update(float deltaTime) override {

        SDL_Event input_event = Game::getInstance()->event;
        UpdateAccordingEvent(input_event);

    }

    void UpdateAccordingEvent(SDL_Event input_event){
        switch(input_event.type){
            case SDL_FINGERDOWN:{
                glm::vec2 touch_pos;
                touch_pos.x = input_event.tfinger.x * static_cast<float>(WINDOW_WIDTH);
                touch_pos.y = input_event.tfinger.y * static_cast<float>(WINDOW_HEIGHT);
                if (m_fingerId == -1) {
                    if(touch_pos.x>buttonDestRect.x
                        &&touch_pos.x<buttonDestRect.x+buttonDestRect.w
                        &&touch_pos.y>buttonDestRect.y
                        &&touch_pos.y<buttonDestRect.y+buttonDestRect.h){

                        m_fingerId = input_event.tfinger.fingerId;
                        isValidTouch = true;
                        buttonTexture = buttonPressedTexture;
                    }
                }
                break;
            }
            case SDL_FINGERMOTION:{
                if (isValidTouch&&input_event.tfinger.fingerId==m_fingerId) {
                    OnButtonPressed();
                }
                break;
            }
            case SDL_FINGERUP:{
                glm::vec2 touch_pos;
                touch_pos.x = input_event.tfinger.x * static_cast<float>(WINDOW_WIDTH);
                touch_pos.y = input_event.tfinger.y * static_cast<float>(WINDOW_HEIGHT);

                if (input_event.tfinger.fingerId==m_fingerId){
                    if(touch_pos.x>buttonDestRect.x
                       &&touch_pos.x<buttonDestRect.x+buttonDestRect.w
                       &&touch_pos.y>buttonDestRect.y
                       &&touch_pos.y<buttonDestRect.y+buttonDestRect.h){
                        //执行按下对应操作
                        OnButtonClick();
                    }
                    isValidTouch = false;
                    buttonTexture = buttonNormalTexture;
                }
                break;
            }

        }







    }

    void Render(float offsetX,float offsetY) override {

        //根据位置渲染button
        TextureManager::DrawTexture(buttonTexture, buttonSourceRect, buttonDestRect, SDL_FLIP_NONE);

    }

    void OnButtonClick(){
        std::list<IControlledByButton*>::iterator itor= controlledThings.begin();

        for (;itor != controlledThings.end(); itor++) {
            (*itor)->DoOnButtonClick();
        }
    }
    void OnButtonPressed(){
        std::list<IControlledByButton*>::iterator itor= controlledThings.begin();

        for (;itor != controlledThings.end(); itor++) {
            (*itor)->DoOnButtonPressed();
        }
    }

    void AttachControlledThing(IControlledByButton* thing) {
        controlledThings.push_back(thing);

    }

    void DetachControlledThing(IControlledByButton* thing) {
        controlledThings.remove(thing);
    }


};


#endif //COMPONENT_BUTTON_H
