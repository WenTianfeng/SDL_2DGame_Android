#include "../HeaderFiles/Game.h"
#include "../HeaderFiles/Constants.h"

int main(int argc,char *args[]){

    Game* game = new Game();

    //Game对象初始化
    game->Initialize(WINDOW_WIDTH,WINDOW_HEIGHT);


    //游戏循环
    while(game->IsRunning()){
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();

    return 0;

}