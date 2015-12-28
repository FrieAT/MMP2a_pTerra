/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "PixelPosition.h"
#include "WorldManager.h"
#include "ObjectManager.h"

PixelPosition::PixelPosition(sf::Vector2f Position, sf::Vector2f Origin)
: IPosition(Position,Origin)
, m_pQuadrant(nullptr)
{
    
}

void PixelPosition::Init()
{
    SetPosition(m_Position);
}

void PixelPosition::SetPosition(sf::Vector2f Position)
{
	this->m_Position = Position;
    UpdateQuadrantPosition();
}
sf::Vector2f PixelPosition::GetPosition()
{
	return (this->m_Position);
}

sf::Vector2f PixelPosition::GetCenter()
{
	return (this->m_Position - this->GetOrigin());
}

float PixelPosition::GetRotation()
{
	return m_fRotation;
}

void PixelPosition::SetOrigin(sf::Vector2f Origin)
{
	this->m_Origin = Origin;
}

sf::Vector2f PixelPosition::GetOrigin()
{
	return m_Origin;
}

void PixelPosition::SetRotation(float rotation)
{
	m_fRotation = rotation;
}

Quadrant* PixelPosition::GetQuadrant()
{
    return m_pQuadrant;
}

void PixelPosition::UpdateQuadrantPosition()
{
    sf::Vector2f ChunkPosition = WorldManager::GetInstance().GetQuadrantCorrectedPos(m_Position);
    std::pair<int, int> ChunkIndex = WorldManager::GetInstance().GetQuadrantIndexAtPos(ChunkPosition);
    Quadrant* pNewQuadrant = WorldManager::GetInstance().GetQuadrant(ChunkIndex);
    if(m_pQuadrant != pNewQuadrant)
    {
        m_pQuadrant = pNewQuadrant;
        ObjectManager::GetInstance().AddGameObject(GetAssignedGameObject());
    }
}