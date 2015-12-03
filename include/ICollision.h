/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"

class ICollision : public IComponent
{
public:

	virtual ~ICollision() { }
	virtual bool colliding(GameObject* Collisionbody) = 0;
	sf::Vector2f restitution;

	EComponentType GetComponentType()
	{
		return EComponentType::Position;
	}

};