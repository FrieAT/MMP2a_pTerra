/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <iostream>

#include "TGUI/TGUI.hpp"

#include "Game.h"

int main(int argc, char const** argv)
{
    // Initialize the "game engine"
	Game* pGameEngine;
	pGameEngine = new Game();
	/*try
	{
		pGameEngine = new Game();
	}
	catch (tgui::Exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "unhandled exception" << std::endl;
	}*/
        
    // Delete all connected ressources and the game engine itself.
    delete pGameEngine;
    
    return EXIT_SUCCESS;
}
