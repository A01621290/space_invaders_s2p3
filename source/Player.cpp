//This is the implementation file of the player
//sub-class defined in the Entity.h header
#include "Entity.h"

Player::Player(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height
        )
    :
        Entity(XPos, YPos,
                Width, Height,
                BASE_PLY_HP,
                4,"./assets/player/player",
                Ent_type::player
              )
{
    CanShoot = true;
    ShootCooldown = BASE_SHT_COOLDOWN;
    XSpeed = 0;
    Moving = false;
}

void Player::setXSpeed(float _XSpeed){
    XSpeed = _XSpeed;
}

void Player::Update(void){
    unsigned short base_frame = 0;

    //Ship will look damaged if below half health
    if (Hp < BASE_PLY_HP/2){
        base_frame += 2;
    }

    //This will play either of the moving animations
    if(Moving){
        CurrentFrame = base_frame + 1;
    }
    //This will play either of the static animations
    else{
        CurrentFrame = base_frame;
    }

    //Will move the player
    XPos += XSpeed;

    //If it can't shoot will either decrease the cooldown
    //or re-enable the ability to shoot
    if(!CanShoot){
        if(ShootCooldown == 0){
            CanShoot = true;
        }
        else{
            ShootCooldown--;
        }
    }

    //Checks if still alive
    Hp <= 0 ? Alive = 0 : Alive;
}

void Player::Collision(Entity& b){
    if(
            *(this) & b &&
            b.getType() == Ent_type::alien_projectile
      ){
        Hp--;
    }
}

Projectile *Player::Shoot(void){
    Projectile *p = new Projectile(
            this->Left() + Width/2, this->Top(),
            2,
            "./assets/player_projectile/projectile",
            Ent_type::player_projectile,
            0.0, BASE_PRJ_SPEED,
            BASE_PRJ_ACC
            );
    return p;
}
