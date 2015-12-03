/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "Quadrant.h"
#include "WorldManager.h"

Quadrant::Quadrant(sf::Vector2f TopLeftPosition)
{
    m_bFreezed = false;
    m_TopLeftPosition = TopLeftPosition;
    m_Index = GetQuadrantIndexAtPos(TopLeftPosition);
    std::cout << "Draw Quadrant at Position: (" << TopLeftPosition.x << " / " << TopLeftPosition.y << ")" << std::endl;
}

std::pair<int,int> Quadrant::GetIndex()
{
    return m_Index;
}

sf::Vector2f Quadrant::GetTopLeftPosition()
{
    return m_TopLeftPosition;
}

bool Quadrant::GetFreezedState()
{
    return m_bFreezed;
}

unsigned Quadrant::RegisterGameObject(GameObject *pObject)
{
    if(pObject == nullptr) return 0;
    m_GameObjects.push_back(pObject);
    return m_GameObjects.size();
}

void Quadrant::UnregisterGameObject(int iIndex)
{
    if((iIndex--) == 0) return;
    m_GameObjects.erase(m_GameObjects.begin() + iIndex);
}

Quadrant* Quadrant::GetNeighbour(EQuadrantPos eChunkPosition, char uChunkDepth)
{
    sf::Vector2f ChunkPosition = CalculatePositionForNeighbour(eChunkPosition);
    Quadrant* FoundQuadrant = WorldManager::GetInstance().GetQuadrant(GetQuadrantIndexAtPos(ChunkPosition));
    if(FoundQuadrant == nullptr) {
        FoundQuadrant = new Quadrant(ChunkPosition);
        WorldManager::GetInstance().AddQuadrant(FoundQuadrant);
        for(int i = 0; uChunkDepth > 0 && i < (int)EQuadrantPos::MaxDirections; i++)
        {
            GetNeighbour((EQuadrantPos)i, --uChunkDepth);
        }
    }
    return FoundQuadrant;
}

std::pair<int,int> Quadrant::GetQuadrantIndexAtPos(sf::Vector2f TopLeftPosition)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(floor(TopLeftPosition.y / ChunkSize.y));
    int dXIndex = static_cast<int>(floor(TopLeftPosition.x / ChunkSize.x));
    return std::pair<int,int>(dXIndex, dYIndex);
}

sf::Vector2f Quadrant::GetQuadrantCorrectedPos(sf::Vector2f Position)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(floor(Position.y / ChunkSize.y));
    int dXIndex = static_cast<int>(floor(Position.x / ChunkSize.x));
    return sf::Vector2f(dXIndex * ChunkSize.x, dYIndex * ChunkSize.y);
}

sf::Vector2f Quadrant::CalculatePositionForNeighbour(EQuadrantPos eChunkPosition)
{
    sf::Vector2f ChunkPosition = m_TopLeftPosition;
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    
    // Verändere ChunkPosition nach gewünschtem EQuadrantPos
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