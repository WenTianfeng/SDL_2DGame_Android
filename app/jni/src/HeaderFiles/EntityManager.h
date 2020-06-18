#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include<vector>

#include"Entity.h"


/*
 * 所有实体的管理器
 * */

class EntityManager{
    private:
        std::vector<Entity*> entities;
    public:
        EntityManager();
        void Update(float deltaTime);
        void Render(float offsetX,float offsetY);
        Entity& AddEntity(std::string entityName,LayerType layer);  //添加实体
        std::vector<Entity*> GetEntities(); //获取所有实体
        std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const; //根据Layer获取实体
        void ClearEntitiesData();
        int GetEntityCount();
        CollisionType CheckCollisions() const;
};

#endif