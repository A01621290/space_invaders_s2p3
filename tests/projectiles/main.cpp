#include "source/Entity.h"
#include "source/WindowManager.h"

int main(int argc, char *argv[]){
    X11 x(0.5, 0.75, 100, 100, "Hello");
    x.Open();
    Projectile *b = new Projectile(x.Att.width/2, x.Att.height, 2, "./assets/player_projectile/projectile", Ent_type::player_projectile, 0.0, 0.0, 0.00001);
    for(;;){
        x.Update();
        if(b != nullptr){
            b->Update();
            b->Draw(x);
            if(!b->getAlive()){
                delete b;
                b = nullptr;
            }
        }
    }
}
