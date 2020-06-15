#ifndef COMPONENT_COLLIDER_H
#define COMPONENT_COLLIDER_H


#include "../HeaderFiles/Game.h"
#include "../Components/ComponentTransform.h"

class ComponentCollider : public Component {
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    ComponentTransform* transform;

    ComponentCollider(std::string colliderTag, int x, int y, int width, int height) {
        this->colliderTag = colliderTag;
        this->collider = { x, y, width, height };
    }

    void Initialize() override {
        if (owner->HasComponent<ComponentTransform>()) {
            transform = owner->GetComponent<ComponentTransform>();
            sourceRectangle = { 0, 0, transform->width, transform->height };
            destinationRectangle = { collider.x, collider.y, collider.w, collider.h };
        }
    }

    void Update(float deltaTime) override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;
    }
};

#endif
