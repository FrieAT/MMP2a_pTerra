#include "GameStatePlay.h"

#include "EventManager.h"
#include "FrameManager.h"
#include "InputManager.h"
#include "ObjectManager.h"

#include "PlayerShip.h"

GameStatePlay::GameStatePlay()
{
    ObjectManager::AddGameObject(new PlayerShip());
    
    // ====== Below decprecated method to create things ======
    
    // Load a sprite to display
    texture = new sf::Texture();
    if (!texture->loadFromFile("assets/cute_image.jpg"))
    {
        throw new std::runtime_error("Unable to load assets/image.jpg");
    }
    sprite = new sf::Sprite(*texture);
    
    // Load a music to play
    music = new sf::Music();
    music->setLoop(true);
    if (!music->openFromFile("assets/nice_music.ogg"))
    {
        throw new std::runtime_error("Unable to load assets/nice_music.ogg");
    }
}

GameStatePlay::~GameStatePlay()
{
    
}

void GameStatePlay::Update(sf::RenderWindow* window)
{
    // Draw the sprite
    window->draw(*sprite);
    
    // Manager updates...
    EventManager::Update(window);
    FrameManager::Update(window);
    InputManager::Update(window);
    ObjectManager::Update(window);
}