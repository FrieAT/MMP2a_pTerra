#include "GameStateIntro.h"

#include "Game.h"
#include "InputManager.h"

GameStateIntro::~GameStateIntro()
{
    InputManager::UnregisterEventObserver(this);
    
    delete texture;
    delete sprite;
}

void GameStateIntro::Init()
{
    KeyPressed = false;
    
    InputManager::RegisterEventObserver(this);
    
    // ====== Below decprecated method to create things ======
    
    // Load a sprite to display
    texture = new sf::Texture();
    if (!texture->loadFromFile("assets/intro-bg.jpg"))
    {
        throw new std::runtime_error("Unable to load assets/intro-bg.jpg");
    }
    sprite = new sf::Sprite(*texture);
}

void GameStateIntro::Update(sf::RenderWindow* window)
{
    // Draw the sprite
    window->draw(*sprite);
}

void GameStateIntro::OnInputUpdate(std::string event)
{
    std::size_t delimiter_pos = event.find('_');
    if(delimiter_pos == std::string::npos) return;
    std::string key = event.substr(0, delimiter_pos);
    std::string state = event.substr(delimiter_pos+1, 1);
    
    if(state == "P" && key == "FIRE" && !KeyPressed)
    {
        KeyPressed = true;
        Game::Engine->ChangeState(new GameStateIntro());
        Game::Engine->Start();
    }
}