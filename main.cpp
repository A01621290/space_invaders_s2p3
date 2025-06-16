#include "./source/GameManager.h"
#define FPS (1/600) * 1000
int main(int argc, char *argv[]){
    Game game;
    game.Open();
    for(;;){
        game.Update();
        game.Draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS));
    }
}
