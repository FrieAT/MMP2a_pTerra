/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "Game.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "WorldManager.h"

GameStatePlay::~GameStatePlay()
{
    // delete m_pMusic;
}

void GameStatePlay::Init()
{
    // Generate estimated World
    WorldManager::GetInstance().GenerateWorld();
    
    // GameObjectFactory::CreatePlayerShip(sf::Vector2f(50,30),'2');
    GameObjectFactory::CreatePlayerShip(sf::Vector2f(50, Game::m_iWindowHeight - 30), '2');
	GameObjectFactory::CreateAsteroid(sf::Vector2f(50,150),-120,50);

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