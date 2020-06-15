#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include<vector>

#include"Entity.h"


class EntityManager{
    private:
        std::vector<Entity*> entities;
    public:
        void Update(float deltaTime);
        void Render();
        Entity& AddEntity(std::string entityName,LayerType layer);
        std::vector<Entity*> GetEntities();
        std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
        void ClearEntitiesData();
        int GetEntityCount();
        CollisionType CheckCollisions() const;
};

#endif