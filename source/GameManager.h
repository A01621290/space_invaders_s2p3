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

class Game{
    X11 X;
    Player Player;
    std::vector<Alien *>Aliens;
    std::vector<Block *>Blocks;
};
