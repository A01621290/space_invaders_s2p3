#include "./source/Entity.h"
#include "./source/WindowManager.h"

int main(int argc, char *argv[]){
    X11 x(0.5, 0.75, 10, 10, "XD");
    Block b(
            100.0, 100.0,
            BASE_WIDTH, BASE_HEIGHT,
            2, "./assets/block/block"
            );
    std::cout<<"Pasa de aquí";
    x.Open();
    for(;;){
        x.Update();
        b.Draw(x);
        b.Update();
    }
}
