/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

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
	return fmodf(m_fRotation + 360.f, 360.f);
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
	m_fRotation = fmodf(rotation + 360.f, 360.f);
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
		// Delete GameObject from old chunk, if a old chunk exists.
		if (m_pQuadrant != nullptr)
		{
			ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject(), false);
		}
		m_pQuadrant = pNewQuadrant;
        ObjectManager::GetInstance().AddGameObject(GetAssignedGameObject());
    }
}

IComponent* PixelPosition::Deserialize(SerializeNode *pNode)
{
    PixelPosition* pComponent = new PixelPosition(sf::Vector2f(), sf::Vector2f());
    
    IPosition::Deserialize(pNode, pComponent);
    
    return pComponent;
}