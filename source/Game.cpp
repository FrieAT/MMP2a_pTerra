#include "Game.h"

#include <iostream>
#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Game::Game()
{
    // Create the main window
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window");
    
    // Set the Icon
    icon = new sf::Image();
    if (!icon->loadFromFile("assets/icon.png"))
    {
        throw new std::runtime_error("Unable to load assets/icon.png");
    }
    window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
}

Game::~Game()
{
    while(!states.empty())
    {
        auto state = states.back();
        delete state;
        states.pop_back();
    }
}

void Game::Start()
{
    IGameState* gamestate;
    
    if(states.empty()) return;
    
    gamestate = states.back();
    
	// Start the game loop
    while (window->isOpen())
	{
		// Clear screen
        window->clear();

        // Call Update in game state
        gamestate->Update(window);

		// Update the window
        window->display();
	}
}

void Game::ChangeState(IGameState* state)
{
    // cleanup the current state
    if ( !states.empty() ) {
        delete states.back();
        states.pop_back();
    }
    
    // store and init the new state
    states.push_back(state);
}