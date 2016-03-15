/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "Game.h"

int main(int argc, char const** argv)
{
    // Initialize the "game engine"
	Game* pGameEngine;
	pGameEngine = new Game();
    delete pGameEngine;
    
    return EXIT_SUCCESS;
}
