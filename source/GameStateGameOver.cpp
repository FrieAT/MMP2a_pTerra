/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "GameStateGameOver.h"

#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"
#include "SpriteDrawing.h"
#include "WorldManager.h"

GameStateGameOver::~GameStateGameOver()
{
    InputManager::GetInstance().UnregisterEventObserver(this);
}

void GameStateGameOver::Init()
{
    m_bKeyPressed = false;
    
    GameObjectFactory::CreateBackgroundSprite("assets/intro-bg.jpg", sf::Vector2f(static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)));
    GameObjectFactory::CreateFontText(sf::Vector2f(280.f, 100.f), "assets/Starjedi.ttf", "game over", 24);
    GameObjectFactory::CreateFontText(sf::Vector2f(230.f, 500.f), "assets/Starjedi.ttf", "-- Press Space-Key to restart game --", 16);
    
    InputManager::GetInstance().RegisterEventObserver(this);
}

void GameStateGameOver::Update(sf::Time DeltaTime, sf::RenderWindow* pWindow)
{

}

void GameStateGameOver::OnInputUpdate(std::string strEvent)
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