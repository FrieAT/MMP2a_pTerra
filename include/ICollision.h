/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"

struct CollisionEvent {
	GameObject* Body1;
	GameObject* Body2;
	sf::Vector2f normal;
};

class ICollision : public IComponent
{
public:
	ICollision() { }
	virtual ~ICollision() { }
	virtual bool colliding(ICollision* Collisionbody) = 0;

	EComponentType GetComponentType()
	{
		return EComponentType::Collision;
	}

};