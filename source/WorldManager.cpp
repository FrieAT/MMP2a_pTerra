/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "WorldManager.h"
#include "ObjectManager.h"
#include "GameObjectFactory.h"

WorldManager::WorldManager(sf::Vector2f ChunkSize, unsigned long MaxRandomCoordinates, char iChunkDepth)
: m_ChunkSize(ChunkSize)
, m_MaxRandomCoordinates(MaxRandomCoordinates)
, m_iChunkDepth(iChunkDepth)
{
    for(unsigned long i = 0; i < m_MaxRandomCoordinates; i++)
    {
        float x = rand() % static_cast<int>(ChunkSize.x);
        float y = rand() % static_cast<int>(ChunkSize.y);
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
    
    const int MaxAsteroidRandItems = 1;
    const int MaxStarsRandItems = 3;
    
    for(int i = 0; i < MaxAsteroidRandItems; i++)
    {
        GameObjectFactory::CreateAsteroid(GetRandomChunkPositionFromChunk(Quadrant), rand() % 360, rand() % 10);
    }
    
    for(int i = 0; i < MaxStarsRandItems; i++)
    {
        GameObjectFactory::CreateBackgroundStar(GetRandomChunkPositionFromChunk(Quadrant));
    }
}

Quadrant* WorldManager::GetQuadrant(std::pair<int,int> QuadrantIndex)
{
    auto it = m_Quadrants.find(QuadrantIndex);
    if(it == m_Quadrants.end()) return nullptr;
    return it->second;
}

std::pair<int,int> WorldManager::GetQuadrantIndexAtPos(sf::Vector2f TopLeftPosition)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(floor(TopLeftPosition.y / ChunkSize.y));
    int dXIndex = static_cast<int>(floor(TopLeftPosition.x / ChunkSize.x));
    return std::pair<int,int>(dXIndex, dYIndex);
}

sf::Vector2f WorldManager::GetQuadrantCorrectedPos(sf::Vector2f Position)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(floor(Position.y / ChunkSize.y));
    int dXIndex = static_cast<int>(floor(Position.x / ChunkSize.x));
    return sf::Vector2f(dXIndex * ChunkSize.x, dYIndex * ChunkSize.y);
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
            if(it->second->GetFreezedState())
            {
                ++it;
                continue;
            }
            sf::RectangleShape shape;
            sf::Color color(255.f, 128.f, 0.f, 128.f);
            sf::Color color_visit(0.f, 0.f, 255, 128.f);
            sf::Color color_look_back(0.f, 255.f, 0.f, 128.f);
            shape.setSize(WorldManager::GetInstance().m_ChunkSize);
            shape.setPosition(it->second->GetTopLeftPosition());
            switch(it->second->m_bCurrentlyVisited)
            {
                case 0:
                    shape.setFillColor(color);
                    break;
                case 1:
                    shape.setFillColor(color_visit);
                    break;
                case 2:
                    shape.setFillColor(color_look_back);
                    break;
            }
            shape.setFillColor((it->second->m_bCurrentlyVisited ? color_visit : color));
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

char WorldManager::GetChunkDepth()
{
    return m_iChunkDepth;
}