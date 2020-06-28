
#ifndef COMPONENT_BATTLE_ATTRIBUTES_H
#define COMPONENT_BATTLE_ATTRIBUTES_H


#include "../HeaderFiles/Component.h"

class ComponentBattleAttributes:public Component{

public:
    int grade;
    int maxHP;
    int currentHP;
    int score;



    ComponentBattleAttributes(int grade,int maxHP,int score){
        this->grade = grade;
        this->maxHP = maxHP;
        this->score = score;
        this->currentHP = maxHP;

    }

    void Update(float deltaTime)
    {

    }



};

#endif //COMPONENT_BATTLE_ATTRIBUTES_H
