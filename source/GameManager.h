/*
 * This header defines the Game class and its respective methods.
 * The Game class will manage when to update and draw the game, as
 * well as simplify the initialization process for all classes
 * and add a simple way to check game physics.
 *
 * Author José Rodrigo Cisneros Murillo
 */

#pragma once
#include <chrono>
#include <thread>
#include "Entity.h"
#include "WindowManager.h"
#define X11_WIDTH 0.4
#define X11_HEIGHT 0.75
#define X11_NAME "Space Invaders"
#define BASE_ALIEN_NUM 32
#define BASE_BLOCK_BUNCHES 6

class Game{
    private:
        std::chrono::time_point<std::chrono::steady_clock> DrawPrevTime;
        std::chrono::time_point<std::chrono::steady_clock> UpdatePrevTime;
        std::chrono::time_point<std::chrono::steady_clock> DrawNowTime;
        std::chrono::time_point<std::chrono::steady_clock> UpdateNowTime;
        std::chrono::steady_clock::duration DrawDeltaTime;
        std::chrono::steady_clock::duration UpdateDeltaTime;
        X11 *X;
        Player *Plyr;
        std::vector<Alien *>Aliens;
        std::vector<Block *>Blocks;
        std::vector<Projectile *>Projectiles;
    public:
        void SetInitialValues(void);    //Sets initial values
        Game(void);                     //Creates new game object
        void Reset(void);               //Resets game object
        void Open(void);                //Opens the game
        void Update(void);              //Updates gameobject
        void Draw(void);                //Draws game object
        void Run(void);                 //Runs the game
        ~Game(void);
};
