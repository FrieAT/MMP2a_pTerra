/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <fstream>

#include "Game.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "FrameManager.h"
#include "AIManager.h"

GameStatePlay::~GameStatePlay()
{
    // delete m_pMusic;
}

void GameStatePlay::Init(sf::RenderWindow* pWindow)
{
    // Generate new World :D
    WorldManager::GetInstance().GenerateWorld();
    
    // GameObjectFactory::CreatePlayerShip(sf::Vector2f(50,30),'2');
    GameObjectFactory::CreatePlayerShip(sf::Vector2f(0.f, 0.f), '2');
	// For testing!!!
	// GameObjectFactory::CreateEnemyShip(sf::Vector2f(0.f, 200.f));
	// For testing!!!
    // GameObjectFactory::CreateAsteroid(sf::Vector2f(50,150),-120,50);

	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Theme.cfg");

    // ====== Below decprecated method to create things ======
    
    // Load a music to play
    /*
    m_pMusic = new sf::Music();
    m_pMusic->setLoop(true);
    if (!m_pMusic->openFromFile("assets/nice_music.ogg"))
    {
        throw std::runtime_error("Unable to load assets/nice_music.ogg");
    }
    m_pMusic->play();
    */
}

void GameStatePlay::SetLoadGame(std::string strLoadGame)
{
    m_strLoadGame = strLoadGame;
    
    // Clear everything.
    ObjectManager::GetInstance().Clear();
    WorldManager::GetInstance().Clear();
    FrameManager::GetInstance().Clear();
    InputManager::GetInstance().Clear();
    CollisionManager::GetInstance().Clear();
    
    // Load the save-game
    WorldManager::GetInstance().LoadGame(m_strLoadGame);
    
    // Refresh cache for generating world upon seed from save-game.
    WorldManager::GetInstance().GenerateWorld();
}

void GameStatePlay::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	// Reset keep in GameStateStorage
	bClearOnGameStateChange = true;

	// Manager updates
	FrameManager::GetInstance().Update(DeltaTime);
	InputManager::GetInstance().Update(pWindow, &m_Gui);
	ObjectManager::GetInstance().Update(DeltaTime);
	CollisionManager::GetInstance().Update(DeltaTime);
	AIManager::GetInstance().Update(DeltaTime);

	// Rendering
	ObjectManager::GetInstance().Draw(pWindow);
    FrameManager::GetInstance().Draw(pWindow);
	//WorldManager::GetInstance().Draw(pWindow); DEBUG
}