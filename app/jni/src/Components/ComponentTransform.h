#ifndef COMPONENT_TRANSFORM_H
#define COMPONENT_TRANSFORM_H


#include"../HeaderFiles/Game.h"
#include"../../UtilLib/glm/glm.hpp"
#include"../Components/ComponentJoystickControl.h"



class ComponentTransform:public Component,public IControlledByJoystick{
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
        ComponentTransform(int posX,int posY,int velX,int velY,int w,int h,int s){
            position = glm::vec2(posX,posY);
            velocity = glm::vec2(velX,velY);
            width = w;
            height = h;
            scale = s;

        }

        virtual ~ComponentTransform() {
        }

        void Initialize() override {

        }

        void Update(float deltaTime) override{
            position.x+=velocity.x*deltaTime;
            position.y+=velocity.y*deltaTime;

        }

        void Render() override{}

        //实现接口函数：随着轮盘输入得到的向量更改自身移动
        virtual void UpdateByJoystick(glm::vec2 normalizedDir) {
            glm::vec2 speed(normalizedDir.x * 150, normalizedDir.y * 150);
            this->velocity.y = speed.y;
            this->velocity.x = speed.x;

        
        }

        //实现接口函数：当轮盘触摸取消，将自身速度归零
        virtual void OnJoystickInvalid() {
            this->velocity.y = 0;
            this->velocity.x = 0;
        }

};


#endif