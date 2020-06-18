#ifndef ENTITY_H
#define ENTITY_H

#include<vector>
#include<string>
#include<map>
#include<typeinfo>

#include"Component.h"
#include"Constants.h"

class EntityManager;//互相引用，前置声明防止错误

/*
 * 实体类
 * */

class Entity{
    private:
        EntityManager& manager;
        bool isActive;
        std::map<const std::type_info*,Component*> componentsMap;
        std::vector<Component*> components;
    public:
        std::string name;
        LayerType layer;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager,std::string name,LayerType layer);

        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        void SetActive(bool);



        //模板函数：添加指定类型的component
        template <typename T,typename...TArgs>
        T& AddComponent(TArgs&&...args){
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentsMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }

        //模板函数：返回指定类型的组件
        template <typename T>
        T* GetComponent(){
            return static_cast<T*>(componentsMap[&typeid(T)]);
        }

        //模板函数：判断实体是否带有指定类型的component
        template <typename T>
        bool HasComponent() {
            return !(componentsMap.find(&typeid(T)) == componentsMap.end());
        }


};

#endif