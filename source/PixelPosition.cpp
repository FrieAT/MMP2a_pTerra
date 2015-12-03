/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "PixelPosition.h"

void PixelPosition::SetPosition(sf::Vector2f Position)
{
	this->m_Position = Position;
}
sf::Vector2f PixelPosition::GetPosition()
{
	return (this->m_Position);
}

sf::Vector2f PixelPosition::GetCenter()
{
	return (this->m_Position + this->GetOrigin());
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
