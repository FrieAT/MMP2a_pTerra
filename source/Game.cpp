/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "Game.h"
#include "FrameManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "WorldManager.h"
#include "AIManager.h"
#include "CollisionManager.h"
#include "GameStateIntro.h"
#include "TextureFactory.h"
#include "ClassRegistry.h"
#include "GUIManager.h"
#include "SoundManager.h"

#include "GameStateIntro.h"
#include "GameStatePlay.h"
#include "GameStateGameOver.h"
#include "GameStatePause.h"

Game* Game::m_pEngine = nullptr;

Game::Game(bool bToggleFullScreen, bool bRotateCamera)
: m_bRotateCamera(bRotateCamera)
{
    if(m_pEngine != nullptr) delete m_pEngine;
    m_pEngine = this;
    m_pCurrentState = nullptr;

	// Initialize ClassRegistry
	ClassRegistry::GetInstance().Init();
    
    // Create the main window
	m_pWindow = new sf::RenderWindow(sf::VideoMode(Game::m_iWindowWidth, Game::m_iWindowHeight), "pTerra" , (bToggleFullScreen ? sf::Style::Fullscreen : sf::Style::Default));

	// Play music
	m_pMusic = new sf::Music();
	m_pMusic->setLoop(true);
	if (!m_pMusic->openFromFile("assets/music.ogg"))
	{
		throw std::runtime_error("Unable to load assets/music.ogg");
	}
	m_pMusic->play();

	// Initialize Intro-screen
	m_pEngine->ChangeState(EGameState::GameStateIntro);
	m_pEngine->Start();
}

Game::~Game()
{
	delete m_pMusic;

    while(!m_States.empty())
    {
        IGameState* pState = m_States.back();
        delete pState;
        m_States.pop_back();
    }

	auto itr = m_mGameStateStorage.begin();
	while (itr != m_mGameStateStorage.end())
	{
		if (itr->second != nullptr)
		{
			delete itr->second;
			itr->second = nullptr;
		}
		++itr;
	}
	m_mGameStateStorage.clear();

	FrameManager::GetInstance().Clear();
	InputManager::GetInstance().Clear();
	ObjectManager::GetInstance().Clear();
	CollisionManager::GetInstance().Clear();
	AIManager::GetInstance().Clear();
    TextureFactory::GetInstance().Clear();
	GUIManager::GetInstance().Clear();
	SoundManager::GetInstance().Clear();
	EventBus::Clear();

	delete m_pWindow;
    m_pEngine = nullptr;
}

void Game::Start()
{    
    IGameState* pGameState;
	sf::Clock DeltaClock;

	m_View = sf::View();
	m_View.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)));
    
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
            if(m_pCurrentState != nullptr && m_pCurrentState->bClearOnGameStateChange)
            {
				// Only clear for GameStatePlay
				if (m_mGameStateStorage[EGameState::GameStatePlay] == m_pCurrentState)
				{
					ObjectManager::GetInstance().Clear();
					WorldManager::GetInstance().Clear();
					FrameManager::GetInstance().Clear();
					InputManager::GetInstance().Clear();
					CollisionManager::GetInstance().Clear();
					AIManager::GetInstance().Clear();
					GUIManager::GetInstance().Clear();
					EventBus::Clear();
				}

				// Set to nullptr in GameStateStorage
				for (auto itr = m_mGameStateStorage.begin(); itr != m_mGameStateStorage.end(); ++itr)
				{
					if (itr->second == m_pCurrentState)
					{
						itr->second = nullptr;
						break;
					}
				}

				// Delete the GameState
                delete m_pCurrentState;
				m_pCurrentState = nullptr;
            }
            
            m_pCurrentState = pGameState;
        }

		// Set current View
		m_pWindow->setView(m_View);

		// Update the state (Updates & Rendering)
		m_pCurrentState->Update(deltaTime, m_pWindow);

		// Update the window
        m_pWindow->display();
	}

	// Before exit set nullptr in GameStateStorage
	for (auto itr = m_mGameStateStorage.begin(); itr != m_mGameStateStorage.end(); ++itr)
	{
		if (itr->second == m_pCurrentState)
		{
			itr->second = nullptr;
			break;
		}
	}
}

void Game::StoreCurrentState(bool value)
{
	if (value)
	{
		m_pCurrentState->bClearOnGameStateChange = false;
	}
	else
	{
		m_pCurrentState->bClearOnGameStateChange = true;
	}
}

bool Game::IsInitialized(EGameState GameState)
{
	return m_mGameStateStorage[GameState] != nullptr;
}

void Game::ChangeState(EGameState GameState)
{
	Game::m_pEngine->m_pWindow->setMouseCursorVisible(true);
	IGameState* pState;

	if (m_mGameStateStorage[GameState] == nullptr)
	{
		switch (GameState)
		{
		case EGameState::GameStateIntro:
			pState = new GameStateIntro();
			break;
		case EGameState::GameStatePlay:
			pState = new GameStatePlay();
			break;
		case EGameState::GameStateGameOver:
			pState = new GameStateGameOver();
			break;
		case EGameState::GameStatePause:
			pState = new GameStatePause();
			break;
		default:
			throw std::invalid_argument("Unknown GameState in Game::ChangeState(EGameState GameState)!");
			break;
		}

		pState->Init(m_pWindow);

		m_mGameStateStorage[GameState] = pState;
	}
	else
	{
		pState = m_mGameStateStorage[GameState];
	}

    // cleanup the current state
    if ( !m_States.empty())
    {
        m_States.pop_back();
    }

    // store and init the new state
    m_States.push_back(pState);
}