#include "Entity.h"

Block::Block(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                unsigned int Anim_Frames, std::string FirstAssetName
            )
    :
        Entity(
                XPos, YPos,
                Width, Height,
                BASE_BLK_HP,
                Anim_Frames, FirstAssetName,
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
            b.getType() == Ent_type::player_projectile &&
            Immunity == false
      ){
        Hp--;
        CurrentFrame++;
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
};

Block::~Block(void){
};
