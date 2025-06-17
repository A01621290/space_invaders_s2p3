//This is the implementation file of the Block
//sub-class defined in the Entity.h header
#include "Entity.h"

Block::Block(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height
            )
    :
        Entity(
                XPos, YPos,
                Width, Height,
                BASE_BLK_HP,
                2, "./assets/block/block",
                Ent_type::block
                )
{
};

//Given an entity b, will check if they collide
//and substract health if it is a player 
//projectile if not immune
void Block::Collision(Entity &b){
    if(
            *this & b &&
            (b.getType() == Ent_type::player_projectile ||
             b.getType() == Ent_type::alien)&&
            Immunity == false
      ){
        Hp--;
        CurrentFrame == 0 ? CurrentFrame++ : CurrentFrame;
    }
};

//
void Block::Update(void){
#ifdef DEBUG
        std::cout << "Updating block. Last hit: " << LastHit << std::endl <<
            << "Immunity: " << Immunity << endl;
#endif
    if(Immunity && LastHit++ > UPDATE_FPS * 1.5){
            Immunity = false;
    }
    else{
        LastHit = 0;
    }

    //Checks if still alive
    (Hp <= 0) ? Alive = 0 : Alive;
};

Block::~Block(void){
};
