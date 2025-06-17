/*
 * This header defines the abstract class Entity
 * Block), as well as its methods and operators
 *
 * Author: José Rodrigo Cisneros Murillo
 */

#pragma once
#include <X11/Xlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "WindowManager.h"
#define X_PIXEL_NUMBER 8
#define Y_PIXEL_NUMBER 8
#define UPDATE_FPS 40
#define BASE_WIDTH 40
#define BASE_HEIGHT 40
#define BASE_PLY_HP 20
#define BASE_ALI_HP 5
#define BASE_PRJ_HP 1
#define BASE_PRJ_SPEED 1
#define BASE_PLYR_SPEED 0.25
#define BASE_BLK_HP 2
#define ALIEN_WAIT_TIME 100
#define BASE_SHT_COOLDOWN UPDATE_FPS * 2
#define ALIEN_SHT_COOLDOWN BASE_SHT_COOLDOWN * 20
#define SIMULATE_W 700

//Enum class defining all entity types
enum class Ent_type{
    player,
    player_projectile,
    alien_projectile,
    alien,
    block
};

//Returns a string with the ent type
std::string getEntType(Ent_type t);

//Function to get the asset file as a string
std::string GetAsset(const std::string file_name);

//Base Abstract Entity class
class Entity{
    protected:
        bool Immunity;                      //Determines if it is currently immune
        bool Alive;                         //If its dead or alive
        unsigned int Anim_Frames;           //Number of frames in the animation
        unsigned int LastHit;               //How many frames ago was entity hit
        long long FrameCounter;             //A counter of total frames
        unsigned int CurrentFrame;          //Current frame playing in the animation
        std::string FirstAssetName;         //Name of the first asset
        std::vector<std::string> Assets;    /*Vector of strings to the asset files
                                              for sprites or animations*/
        Ent_type Type;                      //Enum value determining the kind of entity it is dealing with
    public:
        float XPos, YPos;                   //X and Y positions
        unsigned int Width, Height;         //Width and Height
        short Hp;                           //Current HP
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
        bool getAlive(void);

        virtual void Collision(Entity& b) = 0;        /*Determines what the entity will do when colliding with
                                                        another entity*/
        virtual void Update(void) = 0;                //Update the values of the Entity
};


//Block class
class Block final : public Entity{
    public:
        Block(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height
                );
        void Update(void) override;
        void Collision(Entity& b) override;
        ~Block(void);
};


//Projectile class
class Projectile final : public Entity{
    private:
        float XSpeed, YSpeed;
    public:
        Projectile(
                float XPos, float YPos,
                unsigned int Anim_Frames,
                std::string FirstAssetName,
                Ent_type Type,
                double long XSpeed, double long YSpeed
                );
        void Update(void) override;
        void Collision(Entity& b) override;
};


//Player class
class Player final : public Entity{
    private:
        float XSpeed;   //Player's speed
    public:
        volatile bool CanShoot;
        bool Moving;
        unsigned int ShootCooldown;
        Player(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height
              );
        void setXSpeed(float _XSpeed); //Sets the player XSpeed to a float
        void Update(void) override; //Will update the current animation frame, as well as moving the player
        void Collision(Entity& b) override; //Will lower hp if in contact with an alien projectile
        Projectile *Shoot(void);   //Method to invoke projectiles that go to aliens
};


//Aliens will only shoot when moving
class Alien final : public Entity{
    private:
        bool CanMove;
        unsigned int ShootCooldown;
    public:
        bool CanShoot;
        Alien(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height
                );
        void reduceShootCooldown(void);
        void setYPos(float newPos);
        Projectile *Shoot(float towardsX, float towardsY);
        void Update(void) override;
        void Collision(Entity& b) override;
};

