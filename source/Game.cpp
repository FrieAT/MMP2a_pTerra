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
    if(Engine != nullptr) delete Engine;
    Engine = this;
    
    // Create the main window
    window = new sf::RenderWindow(sf::VideoMode(Game::m_iWindowWidth, Game::m_iWindowHeight), "SFML window");

    // ====== Below decprecated method to create things ======
    // Set the Icon
    if (!icon.loadFromFile("assets/icon.png"))
    {
        throw new std::runtime_error("Unable to load assets/icon.png");
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//set framerate to 60
	window->setFramerateLimit(60);
}

Game::~Game()
{
    while(!states.empty())
    {
        IGameState* state = states.back();
        delete state;
        states.pop_back();
    }

	FrameManager::Clear();
	InputManager::Clear();
	ObjectManager::Clear();

	delete window;
    Engine = nullptr;
}

void Game::Start()
{
    IGameState* gamestate;
	sf::Clock deltaClock;
    
	// Start the game loop
    while (window->isOpen())
	{
		// Get time since last loop
		sf::Time deltaTime = deltaClock.restart();

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
        
        // Manager updates
        EventManager::Update(deltaTime);
        FrameManager::Update(deltaTime);
        InputManager::Update(window);
        ObjectManager::Update(deltaTime);

		// Rendering
        FrameManager::Draw(window);
		ObjectManager::Draw(window);

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