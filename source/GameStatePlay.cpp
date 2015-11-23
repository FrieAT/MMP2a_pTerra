#include "Game.h"
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
    ObjectManager::AddGameObject(GameObjectFactory::CreateBackgroundSprite("assets/space-map.jpg", sf::Vector2f(0.f, Game::m_iWindowHeight)));
    ObjectManager::AddGameObject(GameObjectFactory::CreatePlayerShip(sf::Vector2f(50,30)));
	ObjectManager::AddGameObject(GameObjectFactory::CreatePlayerShip(sf::Vector2f(Game::m_iWindowWidth-50, 30)));

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