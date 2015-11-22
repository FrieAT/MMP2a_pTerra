#include "GameStateIntro.h"

#include "Game.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameStatePlay.h"
#include "GameObjectFactory.h"

GameStateIntro::~GameStateIntro()
{
    InputManager::UnregisterEventObserver(this);
    ObjectManager::RemoveAllGameObjects();
}

void GameStateIntro::Init()
{
    KeyPressed = false;
    
    ObjectManager::AddGameObject(GameObjectFactory::CreateBackgroundSprite("assets/intro-bg.jpg"));
    ObjectManager::AddGameObject(GameObjectFactory::CreateFontText(sf::Vector2f(280.f, 100.f), "assets/Starjedi.ttf", "The Space Game", 24));
    ObjectManager::AddGameObject(GameObjectFactory::CreateFontText(sf::Vector2f(230.f, 500.f), "assets/Starjedi.ttf", "-- Press FIRE-Key to start game --", 16));
    
    InputManager::RegisterEventObserver(this);
}

void GameStateIntro::Update(sf::RenderWindow* window)
{
    
}

void GameStateIntro::OnInputUpdate(std::string event)
{
    std::size_t delimiter_pos = event.find('_');
    if(delimiter_pos == std::string::npos) return;
    std::string key = event.substr(0, delimiter_pos);
    std::string state = event.substr(delimiter_pos+1, 1);
    
    if(state == "P" && key == "FIRE" && !KeyPressed)
    {
        // Prevent of double changing states.
        KeyPressed = true;
        Game::Engine->ChangeState(new GameStatePlay());
    }
}