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
	
	virtual sf::Vector2f GetVelocity() { return velocity; };
	virtual void AddForce(sf::Vector2f force) { impulses.push_back(force); };


	EComponentType GetComponentType()
	{
		return EComponentType::Movement;
	}
protected:
	sf::Clock m_DeltaClock;
	std::list<sf::Vector2f> impulses;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	float mass;
	float invMass;

};
