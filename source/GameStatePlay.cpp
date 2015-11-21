#include "GameStatePlay.h"

#include "GameObjectFactory.h"

#include "ObjectManager.h"

GameStatePlay::~GameStatePlay()
{
    ObjectManager::RemoveAllGameObjects();
    delete texture;
    delete sprite;
    delete music;
}

void GameStatePlay::Init()
{
    //ObjectManager::AddGameObject(new PlayerShip());
	ObjectManager::AddGameObject(GameObjectFactory::CreatePlayerShip());
    
    // ====== Below decprecated method to create things ======
    
    // Load a sprite to display
    texture = new sf::Texture();
    if (!texture->loadFromFile("assets/space-map.jpg"))
    {
        throw new std::runtime_error("Unable to load assets/space-map.jpg");
    }
    sprite = new sf::Sprite(*texture);
    
    // Load a music to play
    music = new sf::Music();
    music->setLoop(true);
    if (!music->openFromFile("assets/nice_music.ogg"))
    {
        throw new std::runtime_error("Unable to load assets/nice_music.ogg");
    }
    music->play();
}

void GameStatePlay::Update(sf::RenderWindow* window)
{
    // Draw the sprite
    window->draw(*sprite);
}