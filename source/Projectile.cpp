#include "Entity.h"

Projectile::Projectile(
    float XPos, float YPos,
    unsigned int Anim_Frames,
    std::string FirstAssetName,
    Ent_type Type,
    double long XSpeed, double long YSpeed,
    double long Acceleration
                )
    :
        Entity(XPos,YPos,
                BASE_WIDTH/4, BASE_HEIGHT/2,
                BASE_PRJ_HP,
                2,
                FirstAssetName,
                Type)
{
    this->Acceleration = Acceleration;
    this->XSpeed = XSpeed;
    this->YSpeed = YSpeed;
}

void Projectile::Update(void){
    if(FrameCounter== UPDATE_FPS * 25){
        CurrentFrame == 0 ? CurrentFrame = 1 : CurrentFrame = 0;
        FrameCounter = 0;
    }
    std::cout << "Speed: (" << XSpeed << ", " << YSpeed << ")\n";
    std::cout << "Acceleration: " << Acceleration << std::endl;
    //Changes position by the given speed
    if(XSpeed != 0){
        if(XSpeed > 0)
            XPos += XSpeed;
        else if(XSpeed < 0)
            XPos -= XSpeed;
        XSpeed += Acceleration;
    }

    //All player shots will go up, and all other shots
    //down
    if(Type == Ent_type::player_projectile){
        YPos -= YSpeed;
    }
    else{
        YPos += YSpeed;
    }

    //Accelerates the shot
    YSpeed += Acceleration;
    FrameCounter++;
}

void Projectile::Collision(Entity &b){
    if(*(this) & b){
        Hp--;
    }
}
