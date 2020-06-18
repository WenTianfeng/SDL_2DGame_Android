#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;//互相引用，前置声明防止错误

/*
 * 组件基类
 * */

class Component{
    public:
        Entity* owner;
        virtual ~Component(){}
        virtual void Initialize(){}
        virtual void Update(float deltaTime){}
        virtual void Render(){}
};

#endif