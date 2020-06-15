#ifndef GAME_H
#define GAME_H

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"

#include"Constants.h"
#include"EntityManager.h"
#include"Component.h"
#include"AssetManager.h"
#include"TerrainMap.h"

#include<iostream>

class AssetManager;


//Game类
class Game{
    private:
        bool isRunning;
        int ticksLastFrame;
        SDL_Window* window;//游戏主窗口
        
    public:
        Game();//构造
        ~Game();//析构
        static SDL_Renderer* renderer;//游戏渲染器
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        bool IsRunning() const;//运行判断
        void Initialize(int width,int height);//初始化
        void LoadLevel(int level);
        void ProcessInput();//输入控制
        void Update();//更新函数
        void Render();//渲染函数
        void Destroy();//销毁函数
        void ProcessNextLevel(int levelNumber);
        void ProcessGameOver();
        void CameraControl();//相机控制
        void CheckCollisions();//碰撞检测

};


#endif // !GAME