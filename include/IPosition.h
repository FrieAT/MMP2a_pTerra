/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"
#include "Quadrant.h"

class IPosition : public IComponent
{
public:
	IPosition(sf::Vector2f Position, sf::Vector2f Origin)
	{
		this->m_Position = Position;
		this->m_fRotation = 0.0;
		this->m_Origin = Origin;
	}
    virtual ~IPosition() { }
	virtual void SetPosition(sf::Vector2f Position) = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual float GetRotation() = 0;
	virtual void SetRotation(float rotation) = 0;
	virtual void SetOrigin(sf::Vector2f Origin) = 0;
	virtual sf::Vector2f GetOrigin() = 0;
    virtual Quadrant* GetQuadrant() { return nullptr; }

	EComponentType GetComponentType()
	{
		return EComponentType::Position;
	}
protected:
	sf::Vector2f m_Position;
	sf::Vector2f m_Origin;
	float m_fRotation;
};