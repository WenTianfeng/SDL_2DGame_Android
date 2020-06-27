#ifndef CONSTANTS_H
#define CONSTANTS_H


/*
 * 全局恒定变量
*/

//显示窗口宽高
const int WINDOW_WIDTH = 2340;
const int WINDOW_HEIGHT = 1080;

//恒定帧率
const int FPS = 60;
const int FRAME_TIME = 1000/FPS;


//实体拥有的Layer属性
enum LayerType {
	LAYER_TILEMAP = 0,
	LAYER_VEGETATION = 1,
	LAYER_ENEMY = 2,
	LAYER_OBSTACLE = 3,
	LAYER_PLAYER = 4,
	LAYER_PROJECTILE = 5,
	LAYER_UI = 6
};

enum Tag{



};


//碰撞类型，用于碰撞检测判断（之后应该修改）
enum CollisionType {
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	PLAYER_VEGETATION_COLLIDER,
	PLAYER_LEVEL_COMPLETE_COLLISION
};


const int LAYER_COUNT = 7;

#endif