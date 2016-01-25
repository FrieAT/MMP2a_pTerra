/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "Game.h"

int main(int argc, char const** argv)
{
	bool bFullScreen = true;

	// Get Arguments
	int current_argc = 1;
	while (current_argc++ < argc)
	{
		std::string param(argv[current_argc - 1]);
		int pos = param.find('=', 0);
		if (pos == std::string::npos)
		{
			continue;
		}
		std::string key = param.substr(0, pos);
		std::string value = param.substr(pos + 1);

		if (key.compare("fullscreen") == 0)
		{
			bFullScreen = (stoi(value) > 0 ? true : false);
		}
	}

    // Initialize the "game engine"
	Game* pGameEngine;
	pGameEngine = new Game(bFullScreen);
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
