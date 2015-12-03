/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "QuadrantPosition.h"
#include "WorldManager.h"
#include "IMovement.h"

QuadrantPosition::QuadrantPosition(sf::Vector2f Position, sf::Vector2f Origin)
: IPosition(Position, Origin)
{
    UpdateQuadrantPosition();
    m_Quadrant = new Quadrant(Position);
    WorldManager::GetInstance().AddQuadrant(m_Quadrant);
}

Quadrant* QuadrantPosition::GetQuadrant()
{
    return m_Quadrant;
}

void QuadrantPosition::UpdateQuadrantPosition()
{
    
}

void QuadrantPosition::SetPosition(sf::Vector2f Position)
{
    this->m_Position = Position;
    
    EQuadrantPos eChunkPosition = GetDirectionKeyFromPos(Position);
    if(eChunkPosition != EQuadrantPos::Null) {
        std::cout << "Search for Neighbour in " << (int)eChunkPosition << std::endl;
        m_Quadrant = m_Quadrant->GetNeighbour(eChunkPosition);
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
    if(m_Quadrant == nullptr)
    {
        return EQuadrantPos::Null;
    }
    
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    sf::Vector2f TopLeftPosition = m_Quadrant->GetTopLeftPosition();
    sf::Vector2f BottomRightPosition((TopLeftPosition.x + ChunkSize.x), (TopLeftPosition.y + ChunkSize.y));
    
    // Prediction Position
    const float predictionFactor = 2.f;
    sf::Vector2f PredictedPosition = Position;
    IMovement* MovementComponent = static_cast<IMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));
    if(MovementComponent != nullptr)
    {
        sf::Vector2f ImpulseDirection = MovementComponent->GetMovementVector();
        std::cout << "Movement Direction: " << ImpulseDirection.x << " / " << ImpulseDirection.y << std::endl;
        // PredictedPosition += ImpulseDirection * predictionFactor;
    }
    
    if(PredictedPosition.x < TopLeftPosition.x && PredictedPosition.y < TopLeftPosition.y)
    {
        return EQuadrantPos::TopLeft;
    }
    else if(PredictedPosition.x > BottomRightPosition.x && PredictedPosition.y < TopLeftPosition.y)
    {
        return EQuadrantPos::TopRight;
    }
    else if(PredictedPosition.x < TopLeftPosition.x && PredictedPosition.y > BottomRightPosition.y)
    {
        return EQuadrantPos::BottomLeft;
    }
    else if(PredictedPosition.x > BottomRightPosition.x && PredictedPosition.y > BottomRightPosition.y)
    {
        return EQuadrantPos::BottomRight;
    }
    else if(PredictedPosition.x < TopLeftPosition.x)
    {
        return EQuadrantPos::Left;
    }
    else if(PredictedPosition.y < TopLeftPosition.y)
    {
        return EQuadrantPos::Top;
    }
    else if(PredictedPosition.x > BottomRightPosition.x)
    {
        return EQuadrantPos::Right;
    }
    else if(PredictedPosition.y > BottomRightPosition.y)
    {
        return EQuadrantPos::Bottom;
    }
    else
    {
        return EQuadrantPos::Null;
    }
}