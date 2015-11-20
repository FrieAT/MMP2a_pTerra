#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"

class IPosition : public IComponent
{
public:
	IPosition(sf::Vector2f Position, sf::Vector2f Origin)
	{
		this->Position = Position;
		this->Rotation = 0.0;
		this->Origin = Origin;
	}
    virtual ~IPosition() { }
	virtual void SetPosition(sf::Vector2f Position) = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual float GetRotation() = 0;
	virtual void SetRotation(float rotation) = 0;
	virtual void SetOrigin(sf::Vector2f Origin) = 0;
	virtual sf::Vector2f GetOrigin() = 0;

	EComponentType GetComponentType()
	{
		return EComponentType::Position;
	}
protected:
	sf::Vector2f Position;
	sf::Vector2f Origin;
	float Rotation;
};