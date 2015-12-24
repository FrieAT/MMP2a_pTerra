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
    ICollision()
    : m_bPhysicsApplyable(true) { }
	virtual ~ICollision() { }
	virtual bool colliding(ICollision* pCollisionBody) = 0;
    bool m_bPhysicsApplyable;
	EComponentType GetComponentType()
	{
		return EComponentType::Collision;
	}
};