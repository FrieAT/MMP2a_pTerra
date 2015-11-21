#include "Game.h"

#include <iostream>
#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "EventManager.h"
#include "FrameManager.h"
#include "InputManager.h"
#include "ObjectManager.h"

Game* Game::Engine = nullptr;

Game::Game()
{
    // Create the main window
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window");
    
    // Set the Icon
    if (!icon.loadFromFile("assets/icon.png"))
    {
        throw new std::runtime_error("Unable to load assets/icon.png");
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    if(Engine != nullptr) delete Engine;
    Engine = this;
}

Game::~Game()
{
    while(!states.empty())
    {
        IGameState* state = states.back();
        delete state;
        states.pop_back();
    }

	delete window;
    Engine = nullptr;
}

void Game::Start()
{
    IGameState* gamestate;
    
	// Start the game loop
    while (window->isOpen())
	{
		// Clear screen
        window->clear();
        
        if(states.empty())
        {
            window->close();
            break;
        }
        
        gamestate = states.back();
        
        // Call Update in game state
        gamestate->Update(window);
        
        // Manager updates...
        EventManager::Update(window);
        FrameManager::Update(window);
        InputManager::Update(window);
        ObjectManager::Update(window);

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
    // Initiate all ressources for new game state
    state->Init();
    // store and init the new state
    states.push_back(state);
}