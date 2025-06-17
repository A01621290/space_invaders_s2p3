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
    ShootCooldown = ALIEN_SHT_COOLDOWN;
}

Projectile *Alien::Shoot(float towardsX, float towardsY){
    CanShoot = false;
    ShootCooldown = ALIEN_SHT_COOLDOWN;
    //deltaX
    float _xdir = towardsX-(XPos+Width/2);
    float _ydir = towardsY-(YPos+Height/2);
    float hyp = std::sqrt(_xdir*_xdir + _ydir*_ydir);
    float _yspeed = BASE_PRJ_SPEED * (_ydir/hyp);
    float _xspeed = BASE_PRJ_SPEED * (_xdir/hyp);

    Projectile *p = new Projectile(
            this->Left() + Width/2, this->Top(),
            2,
            "./assets/alien_projectile/projectile",
            Ent_type::alien_projectile,
            _xspeed, _yspeed
            );
    return p;
}

void Alien::Update(void){
    if(!CanShoot){
        if(ShootCooldown == 0){
            CanShoot = true;
        }
        else{
            ShootCooldown--;
        }
    }
    if(FrameCounter == UPDATE_FPS * ALIEN_WAIT_TIME){
        if(CanMove){
            YPos += Height;
        }
        FrameCounter = 0;
    }
    FrameCounter++;
    if(Hp <= BASE_ALI_HP/2){
        CurrentFrame = 1;
    }
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
