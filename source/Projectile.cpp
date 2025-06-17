//This is the implementation file of the projectile
//sub-class defined in the Entity.h header
#include "Entity.h"

Projectile::Projectile(
    float XPos, float YPos,
    unsigned int Anim_Frames,
    std::string FirstAssetName,
    Ent_type Type,
    double long XSpeed, double long YSpeed
                )
    :
        Entity(XPos,YPos,
                BASE_WIDTH/3, BASE_HEIGHT/1.5,
                BASE_PRJ_HP,
                2,
                FirstAssetName,
                Type)
{
    this->XSpeed = XSpeed;
    this->YSpeed = YSpeed;
}

void Projectile::Update(void){
    if(YPos > 2000 || YPos < -200){
        Hp--;
    }
    if(FrameCounter== UPDATE_FPS){
        CurrentFrame == 0 ? (CurrentFrame = 1) : CurrentFrame = 0;
        FrameCounter = 0;
    }
    FrameCounter++;
    //Changes position by the given speed
    if(XSpeed != 0){
        XPos += XSpeed;
    }

    //All player shots will go up, and all other shots
    //down
    if(Type == Ent_type::player_projectile){
        YPos -= YSpeed;
    }
    else{
        YPos += YSpeed;
    }

    
    //Checks if still alive
    Alive = Hp > 0;
}

void Projectile::Collision(Entity &b){
    if(*(this) & b){
        if(Type == Ent_type::alien_projectile){
            if(b.getType() != Ent_type::alien){
                Hp--;
            }
        }
        if(Type == Ent_type::player_projectile){
            if(b.getType() != Ent_type::player){
                Hp--;
            }
        }
    }
}
