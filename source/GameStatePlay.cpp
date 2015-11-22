#include "GameStatePlay.h"

#include "GameObjectFactory.h"

#include "ObjectManager.h"

GameStatePlay::~GameStatePlay()
{
    ObjectManager::RemoveAllGameObjects();
    delete music;
}

void GameStatePlay::Init()
{
    //ObjectManager::AddGameObject(new PlayerShip());
    ObjectManager::AddGameObject(GameObjectFactory::CreateBackgroundSprite());
    ObjectManager::AddGameObject(GameObjectFactory::CreatePlayerShip());
    
    // ====== Below decprecated method to create things ======
    
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
    
}