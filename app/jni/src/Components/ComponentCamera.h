#ifndef COMPONENT_CAMERA_H
#define COMPONENT_CAMERA_H

#include "../HeaderFiles/Game.h"
#include "../Components/ComponentTransform.h"


class ComponentCamera: public Component{
private:
    Entity* followedEntity;
    //ComponentTransform* transform;



public:
    SDL_Rect visibleRect;
    SDL_Rect rangeRect;

    //有跟随构造方法
    ComponentCamera(Entity* entity, int width, int height, int rangeWidth, int rangeHeight, int rangeX, int rangeY){
        this->followedEntity = entity;

        this->visibleRect.w = width;
        this->visibleRect.h = height;
        this->visibleRect.x = this->followedEntity->GetComponent<ComponentTransform>()->position.x-this->visibleRect.w/2;
        this->visibleRect.y = this->followedEntity->GetComponent<ComponentTransform>()->position.y-this->visibleRect.h/2;

        this->rangeRect.w = rangeWidth;
        this->rangeRect.h = rangeHeight;
        this->rangeRect.x = rangeX;
        this->rangeRect.y = rangeY;


    }
    //无跟随构造方法
    ComponentCamera(int width, int height, int rangeWidth, int rangeHeight, int rangeX, int rangeY){
        this->followedEntity = nullptr;

        this->visibleRect.w = width;
        this->visibleRect.h = height;
        this->visibleRect.x = this->followedEntity->GetComponent<ComponentTransform>()->position.x-this->visibleRect.w/2;
        this->visibleRect.y = this->followedEntity->GetComponent<ComponentTransform>()->position.y-this->visibleRect.h/2;

        this->rangeRect.w = rangeWidth;
        this->rangeRect.h = rangeHeight;
        this->rangeRect.x = rangeX;
        this->rangeRect.y = rangeY;


    }



    void Initialize() override{
        //transform = this->owner->GetComponent<ComponentTransform>();

    }

    void Update(float deltaTime) override{

        if(this->followedEntity!= nullptr){
            visibleRect.x = this->followedEntity->GetComponent<ComponentTransform>()->position.x-this->visibleRect.w/2+this->followedEntity->GetComponent<ComponentTransform>()->width/2;
            visibleRect.y = this->followedEntity->GetComponent<ComponentTransform>()->position.y-this->visibleRect.h/2+this->followedEntity->GetComponent<ComponentTransform>()->height/2;
            visibleRect.x = visibleRect.x < rangeRect.x ? rangeRect.x : visibleRect.x;
            visibleRect.y = visibleRect.y < rangeRect.y ? rangeRect.y : visibleRect.y;
            visibleRect.x = visibleRect.x > rangeRect.x+rangeRect.w-visibleRect.w ? rangeRect.x+rangeRect.w-visibleRect.w : visibleRect.x;
            visibleRect.y = visibleRect.y > rangeRect.y+rangeRect.h-visibleRect.h ? rangeRect.y+rangeRect.h-visibleRect.h : visibleRect.y;


        }


    }

    void Render(float offsetX,float offsetY) override{


    }




};



#endif //COMPONENT_CAMERA_FOLLOW_H
