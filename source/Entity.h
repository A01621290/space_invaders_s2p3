/*
 * This header defines the abstract class Entity
 * and its sub-classes (Player, Alien, Projectile,
 * Block), as well as its methods and operators
 */

#pragma once
#include <X11/Xlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "WindowManager.h"
#define X_PIXEL_NUMBER 8
#define Y_PIXEL_NUMBER 8
#define UPDATE_FPS 40
#define BASE_WIDTH 160
#define BASE_HEIGHT 160
#define BASE_PLY_HP 15
#define BASE_ALI_HP 5
#define BASE_PRJ_HP 1
#define BASE_BLK_HP 2

//Enum class defining all entity types
enum class Ent_type{
    screen,
    player,
    player_projectile,
    alien_projectile,
    alien,
    block
};

//Function to get the asset file as a string
std::string GetAsset(const std::string file_name);

//Base Abstract Entity class
class Entity{
    protected:
        float XPos, YPos;                   //X and Y positions
        unsigned int Width, Height;         //Width and Height
        short Hp;                           //Current HP
        bool Immunity;                      //Determines if it is currently immune
        bool Alive;                         //If its dead or alive
        unsigned int Anim_Frames;           //Number of frames in the animation
        unsigned int LastHit;
        unsigned int CurrentFrame;          //Current frame playing in the animation
        std::string FirstAssetName;         //Name of the first asset
        std::vector<std::string> Assets;    /*Vector of strings to the asset files
                                              for sprites or animations*/
        Ent_type Type;                      //Enum value determining the kind of entity it is dealing with
    public:
        Entity(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                short Hp,
                unsigned int Anim_Frames, std::string FirstAssetName,
                Ent_type Type
                );

        virtual ~Entity(void);                        //Virtual destroyer to avoid memory leaks
        float Top(void) const;                        //These set of methods return the position of the respective side
        float Bottom(void) const;
        float Left(void) const;
        float Right(void) const;
        Ent_type getType(void) const;
        void Draw(const X11 &x11);            //Method to draw each class' assets
        bool operator& (const Entity& b);             //The & operator will check for collisions between entities
        void Print(void);

        virtual void Collision(Entity& b) = 0;        /*Determines what the entity will do when colliding with
                                                        another entity*/
        virtual void Update(void) = 0;                //Update the values of the Entity
};


//Block class
class Block final : public Entity{
    public:
        Block(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                unsigned int Anim_Frames, std::string FirstAssetName
                );
        void Update(void) override;
        void Collision(Entity& b) override;
        ~Block(void);
};


//Projectile class
class Projectile final : public Entity{
    private:
        float XSpeed, YSpeed, Acceleration;
    public:
        Projectile(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                short Hp,
                unsigned int Anim_Frames, std::string FirstAssetName,
                Ent_type Type,
                float XSpeed, float YSpeed,
                float Acceleration
                );
        void Update(void) override;
        void Collision(Entity& b) override;
};


//Player class
class Player final : public Entity{
    private:
        float XSpeed, YSpeed;   //Player's speed
        bool CanShoot;
        unsigned int ShootCooldown;
    public:
        Player(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                short Hp,
                unsigned int Anim_Frames, std::string FirstAssetName,
                Ent_type Type
              );
        void Update(void) override;
        void Collision(Entity& b) override;
        void Shoot(void);   //Method to invoke projectiles that go to aliens
};


class Alien final : public Entity{
    private:
        bool CanShoot;
        unsigned int ShootCooldown;
    public:
        Alien(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                short Hp,
                unsigned int Anim_Frames, std::string FirstAssetName,
                Ent_type Type
                );
        void Shoot(float towardsX, float towardsY);
        void Update(void) override;
        void Collision(Entity& b) override;
};

