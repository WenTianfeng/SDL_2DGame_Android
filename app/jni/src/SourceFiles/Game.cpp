#include "../HeaderFiles/Game.h"
#include"../Components/ComponentTransform.h"
#include"../Components/ComponentSprite.h"
#include"../Components/ComponentCollider.h"
#include"../Components/ComponentTextLabel.h"
#include"../Components/ComponentProjectileLauncher.h"
#include"../Components/ComponentJoystickControl.h"
#include"../Components/ComponentCamera.h"



Game* Game::Instance = nullptr;

Game* Game::getInstance() {

    if(Instance==nullptr){

        Instance = new Game();
    }
    return Instance;

}

//构造函数
Game::Game(){
    entityManager = new EntityManager();
    assetManager = new AssetManager();

    this->isRunning = false;

}

//析构函数
Game::~Game(){


}

//初始化
void Game::Initialize(int width,int height){

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cerr<<"Failed to initialize SDL"<<std::endl;
        return;
    }

    if (TTF_Init() != 0) {
        std::cerr << "Failed to init SDL TTF" << std::endl;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );

    if(!window){
        std::cerr<<"Failed to create SDL window"<<std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window,-1,0);

    if(!renderer){
        std::cerr<<"Failed to create SDL renderer"<<std::endl;
        return;
    }



    LoadLevel(0);

    isRunning = true;

    return;

}



Entity& labelLevelName(Game::getInstance()->entityManager->AddEntity("LabelLevelName", LAYER_UI));
//游戏初始化时加载关卡
void Game::LoadLevel(int level){
    /*资源加载：贴图，字体，地形CSV文件*/

    //加载贴图
    assetManager->AddTexture("image-tank",std::string("images/tank-big-right.png").c_str());
    assetManager->AddTexture("image-chopper", std::string("images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("jungle-tilemap", std::string("tilemaps/jungle.png").c_str());
    assetManager->AddTexture("image-heliport", std::string("images/heliport.png").c_str());
    assetManager->AddTexture("image-button", std::string("images/button.png").c_str());
    assetManager->AddTexture("image-slide-area", std::string("images/slide-area.png").c_str());
    assetManager->AddTexture("image-projectile", std::string("images/bullet-friendly.png").c_str());

    //加载字体
    assetManager->AddFont("font-charriot", std::string("fonts/charriot.ttf").c_str(), 20);

    //地形
    TerrainMap terrainMap("jungle-tilemap", 4, 32);
    terrainMap.LoadTilemap("tilemaps/jungle.txt", 25, 20);

//============================================================================================
    //玩家直升机对象
    Entity& chopper_entity(entityManager->AddEntity("chopper", LAYER_PLAYER));
    chopper_entity.AddComponent<ComponentTransform>(500, 600, 0, 0, 96, 96, 1);
    chopper_entity.AddComponent<ComponentSprite>("image-chopper",2,30,true,false);
    //chopper_entity.AddComponent<ComponentKeyboardControl>("up", "right", "down", "left", "space");
    chopper_entity.AddComponent<ComponentCollider>("PLAYER", 0, 100, 32, 32);
    chopper_entity.AddComponent<ComponentProjectileLauncher>("image-projectile");
//============================================================================================
    //相机初始化
    Entity& mainCamera_entity(entityManager->AddEntity("main-camera",LAYER_PLAYER));
    mainCamera_entity.AddComponent<ComponentCamera>(&chopper_entity,WINDOW_WIDTH,WINDOW_HEIGHT,3200,2560,0,0);
    //设定主相机
    this->mainCamera = &mainCamera_entity;
//============================================================================================
    //坦克对象
    Entity& tank_entity(entityManager->AddEntity("tank",LAYER_ENEMY));
    tank_entity.AddComponent<ComponentTransform>(100,100,0,0,64,64,1);
    tank_entity.AddComponent<ComponentSprite>("image-tank");
    tank_entity.AddComponent<ComponentCollider>("ENEMY", 100, 100, 32, 32);
//============================================================================================
    //停机坪对象
    Entity& heliport(entityManager->AddEntity("heliport", LAYER_OBSTACLE));
    heliport.AddComponent<ComponentTransform>(470, 420, 0, 0, 64, 64, 1);
    heliport.AddComponent<ComponentSprite>("image-heliport");
    heliport.AddComponent<ComponentCollider>("LEVEL_COMPLETE", 470, 420, 32, 32);
//============================================================================================
    //轮盘对象
    //左侧控制轮盘
    Entity& joystick_control_entity(entityManager->AddEntity("joystick-control", LAYER_UI));
    joystick_control_entity.AddComponent<ComponentJoystickControl>("image-button", 128,128,"image-slide-area",50,750,256,256);
    //右侧攻击轮盘
    Entity& joystick_attack_entity(entityManager->AddEntity("joystick-attack", LAYER_UI));
    joystick_attack_entity.AddComponent<ComponentJoystickControl>("image-button",128,128, "image-slide-area",1800,750,256,256);

    //为每个轮盘添加可以控制的组件
    //左侧轮盘控制Transform和Sprite
    joystick_control_entity.GetComponent<ComponentJoystickControl>()->AttachControlledThing(chopper_entity.GetComponent<ComponentTransform>());
    joystick_control_entity.GetComponent<ComponentJoystickControl>()->AttachControlledThing(chopper_entity.GetComponent<ComponentSprite>());
    //右侧轮盘控制Projectile发射器
    joystick_attack_entity.GetComponent<ComponentJoystickControl>()->AttachControlledThing(chopper_entity.GetComponent<ComponentProjectileLauncher>());

//============================================================================================
    //左上角Label
    //Entity& labelLevelName(entityManager->AddEntity("LabelLevelName", LAYER_UI));
    labelLevelName.AddComponent<ComponentTextLabel>(10, 10, "First Level...", "font-charriot", SDL_Color{ 255,255,255,255 });

}

//判断游戏是否运行
bool Game::IsRunning() const {
    return this->isRunning;
}

//输入控制
void Game::ProcessInput(){
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_ESCAPE){
            isRunning = false;
        }
        break;
    
    default:
        break;
    }


}

//更新函数
void Game::Update(){

    //while(!SDL_TICKS_PASSED(SDL_GetTicks(),ticksLastFrame+FRAME_TIME));

    float delta_time = (SDL_GetTicks()-ticksLastFrame)/1000.0f;

    delta_time = (delta_time>0.05f)?0.05f:delta_time;

    ticksLastFrame = SDL_GetTicks();

    entityManager->Update(delta_time);

    //碰撞检测
    CheckCollisions();

    //测试用——显示相机位置
    std::string pos = "X : "+ std::to_string((int)this->mainCamera->GetComponent<ComponentCamera>()->visibleRect.x) +"  Y : "+std::to_string((int)this->mainCamera->GetComponent<ComponentCamera>()->visibleRect.y);
    labelLevelName.GetComponent<ComponentTextLabel>()->SetLabelText(pos,"font-charriot");

}


//渲染函数
void Game::Render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);  

    if(entityManager->GetEntityCount()>0){
        entityManager->Render(this->mainCamera->GetComponent<ComponentCamera>()->visibleRect.x,this->mainCamera->GetComponent<ComponentCamera>()->visibleRect.y);
    }

    SDL_RenderPresent(renderer);

}


void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::CheckCollisions() {
    CollisionType collisionType = entityManager->CheckCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        ProcessNextLevel(1);
    }
}

void Game::ProcessNextLevel(int levelNumber) {
    std::cout << "Next Level" << std::endl;
    isRunning = false;
}

void Game::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}