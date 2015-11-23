/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <iostream>

#include "Game.h"
#include "GameStateIntro.h"
#include "GameStatePlay.h"

int main(int argc, char const** argv)
{
    // Initialize the "game engine"
    Game* pGameEngine = new Game();
    
    // Initialize Intro-screen
	pGameEngine->ChangeState(new GameStateIntro());
	pGameEngine->Start();
    
    // Delete all connected ressources and the game engine itself.
    delete pGameEngine;
    
    return EXIT_SUCCESS;
}
