/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "WorldManager.h"
#include "ObjectManager.h"
#include "GameObjectFactory.h"

WorldManager::WorldManager(sf::Vector2f ChunkSize, unsigned long MaxRandomCoordinates)
: m_ChunkSize(ChunkSize)
, m_MaxRandomCoordinates(MaxRandomCoordinates)
{
    for(unsigned long i = 0; i < m_MaxRandomCoordinates; i++)
    {
        float x = static_cast<float>(rand() % static_cast<int>(ChunkSize.x));
        float y = static_cast<float>(rand() % static_cast<int>(ChunkSize.y));
        m_RandomCoordinates.push_back(sf::Vector2f(x, y));
    }
}

sf::Vector2f WorldManager::GetRandomChunkPositionFromChunk(Quadrant *pChunk)
{
    if(pChunk == nullptr)
    {
        throw std::runtime_error(std::string("Null-reference-expeption in pChunk Object."));
    }
    if(m_IndexRandomCoordinates >= m_RandomCoordinates.size())
    {
        m_IndexRandomCoordinates = 0;
    }
    return (pChunk->GetTopLeftPosition() + m_RandomCoordinates[m_IndexRandomCoordinates++]);
}

void WorldManager::AddQuadrant(Quadrant *Quadrant)
{
    if(Quadrant == nullptr)
    {
        throw std::runtime_error(std::string("A null-reference exception happend by Adding a Quadrant (AddQuadrant)"));
    }
    
    // Ermitlle Index von neuem Quadranten und überprüfe, ob Index nicht bereits benutzt. Sollten alle Unique sein!
    std::pair<int,int> QuadrantIndex = Quadrant->GetIndex();
    if(m_Quadrants[QuadrantIndex] != nullptr)
    {
        throw std::runtime_error(std::string("Unique Index already used, maybe wrong Index set for Quadrant?"));
    }
    m_Quadrants[QuadrantIndex] = Quadrant;
    
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    sf::Vector2f TopLeftPosition = Quadrant->GetTopLeftPosition();
    
    const int MaxAsteroidRandItems = 5;
    const int MaxStarsRandItems = 10;
    
    for(int i = 0; i < MaxAsteroidRandItems; i++)
    {
        GameObject* asteroid = GameObjectFactory::CreateAsteroid(GetRandomChunkPositionFromChunk(Quadrant), static_cast<float>(rand() % 360), static_cast<float>(rand() % 10));
        ObjectManager::GetInstance().AddGameObject(asteroid);
    }
    
    for(int i = 0; i < MaxStarsRandItems; i++)
    {
        GameObject* star_background = GameObjectFactory::CreateBackgroundStar(GetRandomChunkPositionFromChunk(Quadrant));
        ObjectManager::GetInstance().AddGameObject(star_background);
    }
}

Quadrant* WorldManager::GetQuadrant(std::pair<int,int> QuadrantIndex)
{
    auto it = m_Quadrants.find(QuadrantIndex);
    if(it == m_Quadrants.end()) return nullptr;
    return it->second;
}

void WorldManager::Update(sf::RenderWindow *pWindow)
{
    // DEBUG Purpose: Zeige die Quadranten.
    /*
    auto it = m_Quadrants.begin();
    while(it != m_Quadrants.end())
    {
        if(it->second != nullptr)
        {
            sf::RectangleShape shape;
            sf::Color color(255.f, 128.f, 0.f, 128.f);
            shape.setSize(WorldManager::GetInstance().m_ChunkSize);
            shape.setPosition(it->second->GetTopLeftPosition());
            shape.setFillColor(color);
            pWindow->draw(shape);
        }
        ++it;
    }
    */
}

void WorldManager::RegisterEventObserver(IQuadrantObserver* pObserver)
{
    m_Observers.push_back(pObserver);
}

void WorldManager::UnregisterEventObserver(IQuadrantObserver* pObserver)
{
    for(unsigned int i = 0; i < m_Observers.size(); i++)
    {
        if(m_Observers[i] != pObserver) continue;
        m_Observers.erase(m_Observers.begin() + i);
        break;
    }
}

void WorldManager::Clear()
{
    auto it = m_Quadrants.begin();
    while(it != m_Quadrants.end())
    {
        delete(it->second);
        it++;
    }
    m_Quadrants.clear();
    m_Observers.clear();
    m_Observers.shrink_to_fit();
}