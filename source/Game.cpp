/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#include "Game.h"

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "FrameManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "GameStateIntro.h"
#include "TextureFactory.h"

Game* Game::m_pEngine = nullptr;

Game::Game()
{
    if(m_pEngine != nullptr) delete m_pEngine;
    m_pEngine = this;
    
    // Create the main window
    m_pWindow = new sf::RenderWindow(sf::VideoMode(Game::m_iWindowWidth, Game::m_iWindowHeight), "SFML window");

	// Initialize Intro-screen
	m_pEngine->ChangeState(new GameStateIntro());
	m_pEngine->Start();

    // ====== Below decprecated method to create things ======
    // Set the Icon
    if (!m_Icon.loadFromFile("assets/icon.png"))
    {
        throw std::runtime_error("Unable to load assets/icon.png");
    }
    m_pWindow->setIcon(m_Icon.getSize().x, m_Icon.getSize().y, m_Icon.getPixelsPtr());
	//set framerate to 60
	m_pWindow->setFramerateLimit(60);
}

Game::~Game()
{
    while(!m_States.empty())
    {
        IGameState* pState = m_States.back();
        delete pState;
        m_States.pop_back();
    }

	FrameManager::GetInstance().Clear();
	InputManager::GetInstance().Clear();
	ObjectManager::GetInstance().Clear();
	CollisionManager::GetInstance().Clear();
    TextureFactory::GetInstance().Clear();

	delete m_pWindow;
    m_pEngine = nullptr;
}

void Game::Start()
{
    IGameState* pGameState;
	sf::Clock DeltaClock;
    
	// Start the game loop
    while (m_pWindow->isOpen())
	{
		// Get time since last loop
		sf::Time deltaTime = DeltaClock.restart();

		// Clear screen
        m_pWindow->clear();
        
        if(m_States.empty())
        {
            m_pWindow->close();
            break;
        }
        
        pGameState = m_States.back();

        // Manager updates
        FrameManager::GetInstance().Update(deltaTime);
        InputManager::GetInstance().Update(m_pWindow);
        ObjectManager::GetInstance().Update(deltaTime);
        CollisionManager::GetInstance().Update(deltaTime);
        
		// Rendering
        FrameManager::GetInstance().Draw(m_pWindow);
        WorldManager::GetInstance().Update(m_pWindow);
        ObjectManager::GetInstance().Draw(m_pWindow);

		// Update the window
        m_pWindow->display();
	}
}

void Game::ChangeState(IGameState* pState)
{
    // cleanup the current state
    if ( !m_States.empty())
	{
        delete m_States.back();
        
        ObjectManager::GetInstance().Clear();
        WorldManager::GetInstance().Clear();
        FrameManager::GetInstance().Clear();
        InputManager::GetInstance().Clear();
        ObjectManager::GetInstance().Clear();
        CollisionManager::GetInstance().Clear();
        
        m_States.pop_back();
    }
    // Initiate all ressources for new game state
    pState->Init();
    // store and init the new state
    m_States.push_back(pState);
}