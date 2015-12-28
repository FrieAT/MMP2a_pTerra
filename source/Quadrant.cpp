/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "Quadrant.h"
#include "WorldManager.h"
#include "ObjectManager.h"

Quadrant::Quadrant(sf::Vector2f TopLeftPosition)
{
    m_bFreezed = false;
    m_bCurrentlyVisited = 0;
    m_TopLeftPosition = TopLeftPosition;
    m_Index = WorldManager::GetInstance().GetQuadrantIndexAtPos(TopLeftPosition);
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

Quadrant* Quadrant::GetNeighbour(EQuadrantPos eChunkPosition, bool bActive, int uChunkDepth)
{
    Quadrant* FoundQuadrant = &(*this);
    if(eChunkPosition != EQuadrantPos::Null)
    {
        sf::Vector2f ChunkPosition = CalculatePositionForNeighbour(eChunkPosition);
        FoundQuadrant = WorldManager::GetInstance().GetQuadrant(WorldManager::GetInstance().GetQuadrantIndexAtPos(ChunkPosition));
        if(FoundQuadrant == nullptr)
        {
            FoundQuadrant = new Quadrant(ChunkPosition);
            WorldManager::GetInstance().AddQuadrant(FoundQuadrant);
        }
    }
    if(uChunkDepth < 0)
    {
        uChunkDepth = static_cast<int>(WorldManager::GetInstance().GetChunkDepth());
    }
    FoundQuadrant->m_bFreezed = !bActive;
    if(!bActive)
    {
        FoundQuadrant->m_bCurrentlyVisited = 2;
        ObjectManager::GetInstance().RemoveQuadrant(FoundQuadrant);
    }
    else
    {
        FoundQuadrant->m_bCurrentlyVisited = 0;
        ObjectManager::GetInstance().AddQuadrant(FoundQuadrant);
    }
    while((uChunkDepth--) > 0)
    {
        std::cout << "Search in Chunk Depth: " << uChunkDepth << std::endl;
        for(int i = 0; i < (int)EQuadrantPos::MaxDirections; i++)
        {
            FoundQuadrant->GetNeighbour((EQuadrantPos)i, bActive, uChunkDepth);
        }
    }
    return FoundQuadrant;
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