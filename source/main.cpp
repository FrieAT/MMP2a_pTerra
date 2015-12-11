/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <iostream>

#include "Game.h"

int main(int argc, char const** argv)
{
    // Initialize the "game engine"
    Game* pGameEngine = new Game();
        
    // Delete all connected ressources and the game engine itself.
    delete pGameEngine;
    
    return EXIT_SUCCESS;
}
