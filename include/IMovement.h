/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IMovement : public IComponent
{
public:
    virtual ~IMovement() { }

	EComponentType GetComponentType()
	{
		return EComponentType::Movement;
	}
protected:
	sf::Clock m_DeltaClock;
};
