//This is the implementation file of the Alien
//sub-class defined in the Entity.h header
#include "Entity.h"
#include <thread>

Alien::Alien(
        float XPos, float YPos,
        unsigned int Width, unsigned int Height
        )
    :
        Entity(
                XPos, YPos,
                Width, Height,
                BASE_ALI_HP,
                2,
                "./assets/alien/alien",
                Ent_type::alien
              )
{
    CanShoot = false;
    CanMove = true;
    ShootCooldown = BASE_SHT_COOLDOWN * std::rand() % 10;
}

Projectile *Alien::Shoot(float towardsX, float towardsY){
    Projectile *p = new Projectile(
            this->Left() + Width/2, this->Top(),
            2,
            "./assets/alien_projectile/projectile",
            Ent_type::alien_projectile,
            BASE_PRJ_SPEED/2, BASE_PRJ_SPEED/2,
            BASE_PRJ_ACC/2
            );
    return p;
}

void Alien::Update(void){
    if(FrameCounter == UPDATE_FPS * 10){
        if(CanMove){
            YPos += Height;
        }
        CanShoot = true;
        FrameCounter = 0;
    }
    FrameCounter++;
}

void Alien::reduceShootCooldown(void){
    ShootCooldown--;
}

void Alien::setYPos(float newPos){
    YPos = newPos;
}

void Alien::Collision(Entity &b){
    if(*(this) & b){
        if(b.getType() == Ent_type::block || b.getType() == Ent_type::alien){
            CanShoot = false;
            CanMove = false;
        }
        else if(b.getType() == Ent_type::player_projectile){
            Hp--;
        }
    }
}
