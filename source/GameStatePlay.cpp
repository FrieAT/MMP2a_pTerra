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

GameStatePlay::~GameStatePlay()
{
    // delete m_pMusic;
}

void GameStatePlay::Init()
{
    // Check if there is setted a load-file and it really exists.
    std::ifstream ifile(m_strLoadGame);
    if(m_strLoadGame.length() > 0 && ifile)
    {
        // Close dummy check if file exists.
        ifile.close();
        
        // Load the save-game
        WorldManager::GetInstance().LoadGame(m_strLoadGame);
        
        // Refresh cache for generating world upon seed from save-game.
        WorldManager::GetInstance().GenerateWorld();
    }
    else
    {
        // Generate new World :D
        WorldManager::GetInstance().GenerateWorld();
        
        // GameObjectFactory::CreatePlayerShip(sf::Vector2f(50,30),'2');
        GameObjectFactory::CreatePlayerShip(sf::Vector2f(0.f, 0.f), '2');
        
		GameObjectFactory::CreateEnemyShip(sf::Vector2f(0, -200));
		//GameObjectFactory::CreateAsteroid(sf::Vector2f(50,150),-120,50);
    }

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
}