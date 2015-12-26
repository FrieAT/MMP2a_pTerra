/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "GameStateIntro.h"

#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "WorldManager.h"
#include "TextureFactory.h"

GameStateIntro::~GameStateIntro()
{
    InputManager::GetInstance().UnregisterEventObserver(this);
    ObjectManager::GetInstance().RemoveAllGameObjects();
    WorldManager::GetInstance().Clear();
    TextureFactory::GetInstance().Clear();
}

void GameStateIntro::Init()
{
    m_bKeyPressed = false;
    
    ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateBackgroundSprite("assets/intro-bg.jpg", sf::Vector2f(static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight))));
    ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateFontText(sf::Vector2f(280.f, 100.f), "assets/Starjedi.ttf", "The Space Game", 24));
    ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateFontText(sf::Vector2f(230.f, 500.f), "assets/Starjedi.ttf", "-- Press Space-Key to start game --", 16));
    
    InputManager::GetInstance().RegisterEventObserver(this);
}

void GameStateIntro::OnInputUpdate(std::string strEvent)
{
    std::size_t iDelimiterPos = strEvent.find('_');
	if (iDelimiterPos == std::string::npos)
	{
		return;
	}
	std::string strKey = strEvent.substr(1, iDelimiterPos-1);
    std::string strState = strEvent.substr(iDelimiterPos+1, 1);
    
    if(strState == "P" && strKey == "FIRE" && !m_bKeyPressed)
    {
        // Prevent of double changing states.
        m_bKeyPressed = true;
        Game::m_pEngine->ChangeState(new GameStatePlay());
    }
}