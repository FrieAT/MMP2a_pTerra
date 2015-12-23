/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "Game.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"
#include "InputManager.h"

GameStatePlay::~GameStatePlay()
{
    ObjectManager::GetInstance().RemoveAllGameObjects();
    delete m_pMusic;
}

void GameStatePlay::Init()
{
    //ObjectManager::AddGameObject(new PlayerShip());
    ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreatePlayerShip(sf::Vector2f(50,30),'1'));
	//ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreatePlayerShip(sf::Vector2f(50, Game::m_iWindowHeight - 30), '2'));

	ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateAsteroid(sf::Vector2f(50,150),-120,50));

    // ====== Below decprecated method to create things ======
    
    // Load a music to play
    m_pMusic = new sf::Music();
    m_pMusic->setLoop(true);
    if (!m_pMusic->openFromFile("assets/nice_music.ogg"))
    {
        throw std::runtime_error("Unable to load assets/nice_music.ogg");
    }
    // m_pMusic->play();
}