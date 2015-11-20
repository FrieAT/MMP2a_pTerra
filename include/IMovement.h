#pragma once

#include "IComponent.h"

class IMovement : public IComponent
{
public:
    virtual ~IMovement() { }
	virtual void MoveVector(sf::Vector2f &Vector) = 0;

	EComponentType GetComponentType()
	{
		return EComponentType::Movement;
	}
protected:
	sf::Clock deltaClock;
};
