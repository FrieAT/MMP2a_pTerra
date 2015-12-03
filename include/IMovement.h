/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IMovement : public IComponent
{
public:
    virtual ~IMovement() { }
    virtual sf::Vector2f GetImpulseDirection() = 0;
	EComponentType GetComponentType()
	{
		return EComponentType::Movement;
	}
protected:
	sf::Clock m_DeltaClock;
};
