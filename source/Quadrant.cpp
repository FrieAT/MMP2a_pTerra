/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "Quadrant.h"
#include "WorldManager.h"

Quadrant::Quadrant(sf::Vector2f TopLeftPosition)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(TopLeftPosition.y / ChunkSize.y);
    int dXIndex = static_cast<int>(TopLeftPosition.x / ChunkSize.x);
    m_lIndex = (dYIndex + 1) * dXIndex;
    m_bFreezed = false;
    m_TopLeftPosition = sf::Vector2f(dXIndex * ChunkSize.x, dYIndex * ChunkSize.y);
    std::cout << "Given Position (" << TopLeftPosition.x << " / " << TopLeftPosition.y << ") | Changed: (" << m_TopLeftPosition.x << " / " << m_TopLeftPosition.y << ")" << std::endl;
    m_NearQuadrants = std::map<EQuadrantPos, Quadrant*>();
    for(int i = 0; i < (int)EQuadrantPos::MaxDirections; i++) {
        m_NearQuadrants[(EQuadrantPos)i] = nullptr;
    }
}

sf::Vector2f Quadrant::GetTopLeftPosition()
{
    return m_TopLeftPosition;
}

bool Quadrant::GetFreezedState()
{
    return m_bFreezed;
}

long Quadrant::GetIndex()
{
    return m_lIndex;
}

unsigned Quadrant::RegisterGameObject(GameObject *pObject)
{
    if(pObject == nullptr) return 0;
    m_GameObjects.push_back(pObject);
    return m_GameObjects.size();
}

void Quadrant::UnregisterGameObject(unsigned iIndex)
{
    if((iIndex--) == 0) return;
    m_GameObjects.erase(m_GameObjects.begin() + iIndex);
}

Quadrant* Quadrant::GetNeighbour(EQuadrantPos eChunkPosition)
{
    Quadrant* FoundQuadrant = m_NearQuadrants[eChunkPosition];
    if(FoundQuadrant == nullptr) {
        FoundQuadrant = new Quadrant(CalculatePositionForNeighbour(eChunkPosition));
        m_NearQuadrants[eChunkPosition] = FoundQuadrant;
        WorldManager::GetInstance().AddQuadrant(FoundQuadrant);
    }
    return FoundQuadrant;
}

sf::Vector2f Quadrant::CalculatePositionForNeighbour(EQuadrantPos eChunkPosition)
{
    sf::Vector2f ChunkPosition = m_TopLeftPosition;
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    if(eChunkPosition == EQuadrantPos::TopLeft)
    {
        ChunkPosition.x -= ChunkSize.x;
        ChunkPosition.y -= ChunkSize.y;
    }
    else if(eChunkPosition == EQuadrantPos::TopRight)
    {
        ChunkPosition.x += ChunkSize.x;
        ChunkPosition.y -= ChunkSize.y;
    }
    else if(eChunkPosition == EQuadrantPos::BottomLeft)
    {
        ChunkPosition.x -= ChunkSize.x;
        ChunkPosition.y += ChunkSize.y;
    }
    else if(eChunkPosition == EQuadrantPos::BottomRight)
    {
        ChunkPosition.x += ChunkSize.x;
        ChunkPosition.y += ChunkSize.y;
    }
    else if(eChunkPosition == EQuadrantPos::Top)
    {
        ChunkPosition.y -= ChunkSize.y;
    }
    else if(eChunkPosition == EQuadrantPos::Left)
    {
        ChunkPosition.x -= ChunkSize.x;
    }
    else if(eChunkPosition == EQuadrantPos::Right)
    {
        ChunkPosition.x += ChunkSize.x;
    }
    else if(eChunkPosition == EQuadrantPos::Bottom)
    {
        ChunkPosition.y += ChunkSize.y;
    }
    else
    {
        throw std::runtime_error(std::string("Invalid EQuadrantPosition given to calculation."));
    }
    return ChunkPosition;
}