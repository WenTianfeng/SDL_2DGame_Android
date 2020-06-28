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


//Game类
class Game{

    private:
        bool isRunning;
        int ticksLastFrame;
        SDL_Window* window;//游戏主窗口
        Game();
        Game(const Game& other);
        
    public:

        static Game* getInstance();
        static Game* Instance;
        ~Game();//析构
        SDL_Renderer* renderer;//游戏渲染器
        AssetManager* assetManager;
        EntityManager* entityManager;
        SDL_Event event;
        Entity* mainCamera;

        bool IsRunning() const;//运行判断
        void Initialize(int width,int height);//初始化
        void ProcessInput();//输入控制
        void Update();//更新函数
        void Render();//渲染函数
        void Destroy();//销毁函数
        void CheckCollisions();//碰撞检测
        void LoadMenu();
        void LoadLevel(int level);
        void ProcessNextLevel(int levelNumber);
        void ProcessGameOver();


};




#endif // !GAME