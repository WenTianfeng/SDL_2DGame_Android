#ifndef COLLISION_H
#define COLLISION_H

#include "Game.h"


/*
 * 碰撞检测类
 * */

class Collision {
public:
    static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB);
};

#endif
