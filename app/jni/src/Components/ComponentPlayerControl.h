#ifndef COMPONENT_PLAYER_CONTROL_H
#define COMPONENT_PLAYER_CONTROL_H

#include "../HeaderFiles/Component.h"

#include "ComponentBattleAttributes.h"
#include "ComponentTextLabel.h"

class ComponentPlayerControl:public Component{

    ComponentBattleAttributes* myAttributes;
    ComponentTextLabel* myHPLabel;
    ComponentTextLabel* myScoreLabel;

public:
    ComponentPlayerControl(ComponentBattleAttributes* myAttributes,ComponentTextLabel* myHPLabel,ComponentTextLabel* myScoreLabel){
        this->myAttributes = myAttributes;
        this->myHPLabel = myHPLabel;
        this->myScoreLabel = myScoreLabel;

    }

    void Initialize()override{


    }

    void Update(float deltaTime) override {
        std::string hp_text = "HP : "+std::to_string(myAttributes->currentHP);
        myHPLabel->SetLabelText(hp_text);
        std::string score_text = "SCORE : "+std::to_string(myAttributes->score);
        myScoreLabel->SetLabelText(score_text);


    }

    void Render(float offsetX,float offsetY) override{

    }


};


#endif //COMPONENT_PLAYER_CONTROL_H
