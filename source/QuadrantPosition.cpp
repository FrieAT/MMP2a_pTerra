/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "QuadrantPosition.h"
#include "WorldManager.h"
#include "ObjectManager.h"
#include "IMovement.h"

QuadrantPosition::QuadrantPosition(sf::Vector2f Position, sf::Vector2f Origin)
: IPosition(Position, Origin)
, m_ELastDirection(EQuadrantPos::Null)
{
    m_pQuadrant = new Quadrant(Position);
    WorldManager::GetInstance().AddQuadrant(m_pQuadrant);
    m_pQuadrant->GetNeighbour(EQuadrantPos::Null, true);
}

void QuadrantPosition::Init()
{
    ObjectManager::GetInstance().AddGameObject(GetAssignedGameObject());
}

Quadrant* QuadrantPosition::GetQuadrant()
{
    return m_pQuadrant;
}

void QuadrantPosition::SetPosition(sf::Vector2f Position)
{
    this->m_Position = Position;
    
    // Prediction Position
    /*
    IMovement* MovementComponent = static_cast<IMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));
    if(MovementComponent != nullptr)
    {
        sf::Vector2f ImpulseDirection = MovementComponent->GetVelocity();
        // std::cout << "Movement Direction: " << ImpulseDirection.x << " / " << ImpulseDirection.y << std::endl;
        Position += ImpulseDirection;
    }
    */
    
    // WorldManager* WorldMgrInstance = &WorldManager::GetInstance();
    // m_Quadrant = WorldMgrInstance->GetQuadrant(WorldMgrInstance->GetQuadrantIndexAtPos(WorldMgrInstance->GetQuadrantCorrectedPos(this->m_Position)));
    
    EQuadrantPos eNextChunkPosition = GetDirectionKeyFromPos(Position);
    if(eNextChunkPosition != EQuadrantPos::Null) {
        if(m_ELastDirection != EQuadrantPos::Null)
        {
            EQuadrantPos eReverseChunkPosition = (EQuadrantPos)((int)m_ELastDirection - 4 < 0 ? (int)EQuadrantPos::MaxDirections + ((int)m_ELastDirection - 4) : (int)m_ELastDirection - 4);
            Quadrant* pPreNeighbour = m_pQuadrant;
            int iDepth = static_cast<int>(WorldManager::GetInstance().GetChunkDepth());
            while((iDepth--) > 0)
            {
                pPreNeighbour = pPreNeighbour->GetNeighbour(eReverseChunkPosition, false, 0);
            }
            pPreNeighbour->GetNeighbour(eReverseChunkPosition, false, static_cast<int>(WorldManager::GetInstance().GetChunkDepth()) + 1);
        }
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject(), false); //< Remove game object from old chunk.
        m_pQuadrant = m_pQuadrant->GetNeighbour(eNextChunkPosition, true);
        m_pQuadrant->m_bCurrentlyVisited = 1;
        m_ELastDirection = eNextChunkPosition;
        ObjectManager::GetInstance().AddGameObject(GetAssignedGameObject());
    }
}

sf::Vector2f QuadrantPosition::GetPosition()
{
    return (this->m_Position);
}

float QuadrantPosition::GetRotation()
{
    return m_fRotation;
}

void QuadrantPosition::SetOrigin(sf::Vector2f Origin)
{
    this->m_Origin = Origin;
}

sf::Vector2f QuadrantPosition::GetOrigin()
{
    return m_Origin;
}

sf::Vector2f QuadrantPosition::GetCenter()
{
    return (this->m_Position + this->GetOrigin());
}

void QuadrantPosition::SetRotation(float rotation)
{
    m_fRotation = rotation;
}

EQuadrantPos QuadrantPosition::GetDirectionKeyFromPos(sf::Vector2f Position)
{
    if(m_pQuadrant == nullptr)
    {
        return EQuadrantPos::Null;
    }
    
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    sf::Vector2f TopLeftPosition = m_pQuadrant->GetTopLeftPosition();
    sf::Vector2f BottomRightPosition((TopLeftPosition.x + ChunkSize.x), (TopLeftPosition.y + ChunkSize.y));
    
    if(Position.x < TopLeftPosition.x && Position.y < TopLeftPosition.y)
    {
        return EQuadrantPos::TopLeft;
    }
    else if(Position.x > BottomRightPosition.x && Position.y < TopLeftPosition.y)
    {
        return EQuadrantPos::TopRight;
    }
    else if(Position.x < TopLeftPosition.x && Position.y > BottomRightPosition.y)
    {
        return EQuadrantPos::BottomLeft;
    }
    else if(Position.x > BottomRightPosition.x && Position.y > BottomRightPosition.y)
    {
        return EQuadrantPos::BottomRight;
    }
    else if(Position.x < TopLeftPosition.x)
    {
        return EQuadrantPos::Left;
    }
    else if(Position.y < TopLeftPosition.y)
    {
        return EQuadrantPos::Top;
    }
    else if(Position.x > BottomRightPosition.x)
    {
        return EQuadrantPos::Right;
    }
    else if(Position.y > BottomRightPosition.y)
    {
        return EQuadrantPos::Bottom;
    }
    else
    {
        return EQuadrantPos::Null;
    }
}