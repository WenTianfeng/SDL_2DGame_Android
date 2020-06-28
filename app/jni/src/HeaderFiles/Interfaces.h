#ifndef INTERFACES_H
#define INTERFACES_H

#include"../../UtilLib/glm/glm.hpp"
/*
轮盘控制的信息接收者需要继承的接口
*/
class IControlledByJoystick {

public:
    ~IControlledByJoystick() {}
    virtual void UpdateByJoystick(glm::vec2 normalizedDir) = 0;
    virtual void OnJoystickInvalid() = 0;
};

class IControlledByAI{

public:
    ~IControlledByAI() {}
    virtual void DoOnStateAttack() = 0;
    virtual void DoOnStateIdle() = 0;
};

class IControlledByButton{

public:
    ~IControlledByButton(){}

    virtual void DoOnButtonClick() = 0;
    virtual void DoOnButtonPressed() = 0;

};





#endif
