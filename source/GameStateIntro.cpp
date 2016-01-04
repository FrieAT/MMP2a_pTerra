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

GameStateIntro::~GameStateIntro()
{
    InputManager::GetInstance().UnregisterEventObserver(this);
}

void GameStateIntro::Init(sf::RenderWindow* pWindow)
{
    m_bKeyPressed = false;
    
    GameObjectFactory::CreateBackgroundSprite("assets/intro-bg.jpg", sf::Vector2f(static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)));
    GameObjectFactory::CreateFontText(sf::Vector2f(280.f, 100.f), "assets/Starjedi.ttf", "The Space Game", 24);
    GameObjectFactory::CreateFontText(sf::Vector2f(230.f, 500.f), "assets/Starjedi.ttf", "-- Press Space-Key to start game --", 16);
    
	// Initialize GUI
	m_Gui.setWindow(*pWindow);
	m_Gui.setFont("assets/Starjedi.ttf");
	auto theme = std::make_shared<tgui::Theme>("Black.txt");


    InputManager::GetInstance().RegisterEventObserver(this);
}

void GameStateIntro::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{
	// Manager updates
	

	// Rendering
	
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