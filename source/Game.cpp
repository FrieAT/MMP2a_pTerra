/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#include "Game.h"

#include <iostream>

#include "FrameManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "GameStateIntro.h"
#include "TextureFactory.h"
#include "ClassRegistry.h"

Game* Game::m_pEngine = nullptr;

Game::Game()
{
    if(m_pEngine != nullptr) delete m_pEngine;
    m_pEngine = this;
    m_pCurrentState = nullptr;
    
    // Create the main window
	m_pWindow = new sf::RenderWindow(sf::VideoMode(Game::m_iWindowWidth, Game::m_iWindowHeight), "pTerra");//, sf::Style::Fullscreen);

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
    ClassRegistry::GetInstance().Init();
    
    IGameState* pGameState;
	sf::Clock DeltaClock;

	// Set view (Otherwise Debug build won't properly display on start-up)
	sf::View view(sf::FloatRect(0.f, 0.f, Game::m_iWindowWidth, Game::m_iWindowHeight));
	m_pWindow->setView(view);
    
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
        
        if(pGameState != m_pCurrentState)
        {
            if(m_pCurrentState != nullptr && m_pCurrentState->ClearOnGameStateChange())
            {
                delete m_pCurrentState;
                
                ObjectManager::GetInstance().Clear();
                WorldManager::GetInstance().Clear();
                FrameManager::GetInstance().Clear();
                InputManager::GetInstance().Clear();
                ObjectManager::GetInstance().Clear();
                CollisionManager::GetInstance().Clear();
            }
            
            m_pCurrentState = pGameState;

			if (m_pCurrentState->IsInitialized() == false)
			{
				m_pCurrentState->Init(m_pWindow);
			}
        }

		// Update the state (Updates & Rendering)
		m_pCurrentState->Update(deltaTime, m_pWindow);

		// Update the window
        m_pWindow->display();
	}
}

void Game::ChangeState(IGameState* pState)
{
	// create new state


    // cleanup the current state
    if ( !m_States.empty())
    {
        m_States.pop_back();
    }

    // store and init the new state
    m_States.push_back(pState);
}