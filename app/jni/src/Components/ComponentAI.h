#ifndef COMPONENT_AI_H
#define COMPONENT_AI_H


#include <list>
#include "../HeaderFiles/Game.h"
#include"../../UtilLib/glm/glm.hpp"
#include "../HeaderFiles/Interfaces.h"
#include "ComponentTransform.h"



enum AIStates{
    STATE_IDLE = 0,
    STATE_ATTACK=1
};

class ComponentAI:public Component{

private:
    AIStates state;


    int alertRange;

    std::list<IControlledByAI*> controlledThings;
    ComponentTransform* transform;

public:
    Entity* rival;

    ComponentAI(Entity* rival,int alertRange){
        this->rival = rival;
        this->alertRange = alertRange;
    }

    void Initialize() override {
        state = STATE_IDLE;
        transform = owner->GetComponent<ComponentTransform>();


    }

    void Update(float deltaTime) override {

        StateProcess();

        switch (state){
            case STATE_IDLE:{
                std::list<IControlledByAI*>::iterator itor= controlledThings.begin();

                for (; itor != controlledThings.end(); itor++) {
                    (*itor)->DoOnStateIdle();
                }

                break;
            }
            case STATE_ATTACK:{
                std::list<IControlledByAI*>::iterator itor= controlledThings.begin();

                for (; itor != controlledThings.end(); itor++) {
                    (*itor)->DoOnStateAttack();
                }

                break;
            }


        }

    }

    void AttachControlledThing(IControlledByAI* thing) {
        controlledThings.push_back(thing);

    }

    void DetachControlledThing(IControlledByAI* thing) {
        controlledThings.remove(thing);
    }

    void StateProcess(){

        auto distance = std::sqrt(std::pow(transform->position.x - rival->GetComponent<ComponentTransform>()->position.x, 2)
                + std::pow(transform->position.y - rival->GetComponent<ComponentTransform>()->position.y, 2));

        if(distance<=alertRange&&state!=STATE_ATTACK){
            state = STATE_ATTACK;

        }else if(distance>alertRange&&state!=STATE_IDLE){
            state = STATE_IDLE;

        }else{


        }


    }



};


#endif //COMPONENT_AI_H
