/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"
#include <list>

class IMovement : public IComponent
{
public:
    virtual ~IMovement() { }
	
	virtual sf::Vector2f GetMovementVector() = 0;
	//virtual void AddForce(sf::Vector2f) = 0;

	float mass;
	float invMass;

	sf::Vector2f position;

	std::list<sf::Vector2f> impulses;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;

	EComponentType GetComponentType()
	{
		return EComponentType::Movement;
	}
protected:
	sf::Clock m_DeltaClock;
};
