#include"../HeaderFiles/EntityManager.h"
#include "../HeaderFiles/Coliision.h"
#include "../Components/ComponentCollider.h"

void EntityManager::ClearEntitiesData(){
    for (auto& entity:entities)
    {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime){
    for (auto& entity:entities)
    {
        entity->Update(deltaTime);
    }

    for (int i = 0; i < entities.size(); ++i) {
        if(!entities[i]->IsActive()){
            entities.erase(entities.begin()+i);
        }
    }
    

}
void EntityManager::Render(){
    

    for (int layerNum= 0;  layerNum<LAYER_COUNT; layerNum++)
    {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNum)))
        {
            entity->Render();
        }
    }


}

Entity& EntityManager::AddEntity(std::string entityName,LayerType layer){
    Entity* entity = new Entity(*this,entityName,layer);
    entities.emplace_back(entity);
    return *entity;

}

std::vector<Entity*> EntityManager::GetEntities(){
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const{
    std::vector<Entity*> selectedEntities;
    for (auto& entity :entities)
    {
        if (entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }

    return selectedEntities;
}

int EntityManager::GetEntityCount(){
    return entities.size();

}



CollisionType EntityManager::CheckCollisions() const {
    for (int i = 0; i < entities.size() - 1; i++) {
        auto& thisEntity = entities[i];
        if (thisEntity->HasComponent<ComponentCollider>()) {
            ComponentCollider* thisCollider = thisEntity->GetComponent<ComponentCollider>();
            for (int j = i + 1; j < entities.size(); j++) {
                auto& thatEntity = entities[j];
                if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ComponentCollider>()) {
                    ComponentCollider* thatCollider = thatEntity->GetComponent<ComponentCollider>();
                    if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0) {
                            return PLAYER_ENEMY_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0) {
                            return PLAYER_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) {
                            return ENEMY_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) {
                            return PLAYER_LEVEL_COMPLETE_COLLISION;
                        }
                    }
                }
            }
        }
    }
    return NO_COLLISION;
}