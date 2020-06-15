
#include "../HeaderFiles/Game.h"
#include"../Components/ComponentTransform.h"
#include"../Components/ComponentSprite.h"
#include"../Components/ComponentKeyboardControl.h"
#include"../Components/ComponentCollider.h"
#include"../Components/ComponentTextLabel.h"
#include"../Components/ComponentProjectileLauncher.h"
#include"../Components/ComponentJoystickControl.h"






//For Test
EntityManager manager;
AssetManager* Game::assetManager = new AssetManager();
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };

//构造函数
Game::Game(){
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

Entity& chopper_entity(manager.AddEntity("chopper", LAYER_PLAYER));
Entity& labelLevelName(manager.AddEntity("LabelLevelName", LAYER_UI));

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
    terrainMap.LoadMapCSV("tilemaps/jungle.txt", 25, 20);



    
    //玩家直升机对象
    chopper_entity.AddComponent<ComponentTransform>(500, 600, 0, 0, 96, 96, 1);
    chopper_entity.AddComponent<ComponentSprite>("image-chopper",2,30,true,false);
    //chopper_entity.AddComponent<ComponentKeyboardControl>("up", "right", "down", "left", "space");
    chopper_entity.AddComponent<ComponentCollider>("PLAYER", 0, 100, 32, 32);
    chopper_entity.AddComponent<ComponentProjectileLauncher>("image-projectile");

    //坦克对象
    Entity& tank_entity(manager.AddEntity("tank",LAYER_ENEMY));
    tank_entity.AddComponent<ComponentTransform>(100,100,0,0,64,64,1);
    tank_entity.AddComponent<ComponentSprite>("image-tank");
    tank_entity.AddComponent<ComponentCollider>("ENEMY", 100, 100, 32, 32);

    //停机坪对象
    Entity& heliport(manager.AddEntity("heliport", LAYER_OBSTACLE));
    heliport.AddComponent<ComponentTransform>(470, 420, 0, 0, 64, 64, 1);
    heliport.AddComponent<ComponentSprite>("image-heliport");
    heliport.AddComponent<ComponentCollider>("LEVEL_COMPLETE", 470, 420, 32, 32);

    //轮盘对象
    //左侧控制轮盘
    Entity& joystick_control_entity(manager.AddEntity("joystick-control", LAYER_UI));
    joystick_control_entity.AddComponent<ComponentJoystickControl>("image-button", 128,128,"image-slide-area",50,750,256,256);
    //右侧攻击轮盘
    Entity& joystick_attack_entity(manager.AddEntity("joystick-attack", LAYER_UI));
    joystick_attack_entity.AddComponent<ComponentJoystickControl>("image-button",128,128, "image-slide-area",1800,750,256,256);

    //为每个轮盘添加可以控制的组件
    //左侧轮盘控制Transform和Sprite
    joystick_control_entity.GetComponent<ComponentJoystickControl>()->AttachControlledThing(chopper_entity.GetComponent<ComponentTransform>());
    joystick_control_entity.GetComponent<ComponentJoystickControl>()->AttachControlledThing(chopper_entity.GetComponent<ComponentSprite>());
    //右侧轮盘控制Projectile发射器
    joystick_attack_entity.GetComponent<ComponentJoystickControl>()->AttachControlledThing(chopper_entity.GetComponent<ComponentProjectileLauncher>());


    //左上角Label

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

    manager.Update(delta_time);
    std::string pos = "X : "+ std::to_string((int)chopper_entity.GetComponent<ComponentTransform>()->position.x) +"  Y : "+std::to_string((int)chopper_entity.GetComponent<ComponentTransform>()->position.y);


    labelLevelName.GetComponent<ComponentTextLabel>()->SetLabelText(pos,"font-charriot");

    CameraControl();
    CheckCollisions();
}


//渲染函数
void Game::Render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);  

    if(manager.GetEntityCount()==0){
        return;
    }


    manager.Render();
    
    SDL_RenderPresent(renderer);

}


//  相机控制.
void Game::CameraControl() {
    ComponentTransform* playerTransform = chopper_entity.GetComponent<ComponentTransform>();

    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    //camera.x = camera.x > camera.w ? camera.w : camera.x;
    //camera.y = camera.y > camera.h ? camera.h : camera.y;



}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::CheckCollisions() {
    CollisionType collisionType = manager.CheckCollisions();
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