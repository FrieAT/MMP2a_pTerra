#include "stdafx.h"

#include "AIStatePatrol.h"
#include "ShipMovement.h"
#include "IPosition.h"
#include "ObjectManager.h"
#include "IScore.h"

#define _USE_MATH_DEFINES
#include <math.h>

AIStatePatrol::AIStatePatrol()
{
}


AIStatePatrol::~AIStatePatrol()
{
}

void AIStatePatrol::Update(GameObject* obj)
{
	IPosition* ppos = static_cast<IPosition*>(obj->GetComponent(EComponentType::Position));
	ShipMovement* pmov = static_cast<ShipMovement*>(obj->GetComponent(EComponentType::Movement));

	// Get current rotation
	float currentRotation = ppos->GetRotation();
	sf::Vector2f velocity = pmov->GetVelocity();
	float reverseVelocityAngle = std::fmodf((std::atan2f(velocity.y, velocity.x) * 180.f / M_PI + 450 + 180), 360.f);

	float diffLeft;
	float diffRight;
	if (currentRotation < reverseVelocityAngle)
	{
		diffLeft = currentRotation + 360 - reverseVelocityAngle;
		diffRight = reverseVelocityAngle - currentRotation;
	}
	else
	{
		diffLeft = currentRotation - reverseVelocityAngle;
		diffRight = 360 - currentRotation + reverseVelocityAngle;
	}

	if (diffLeft < diffRight)	//turn left
	{
		if (diffLeft < 10)
		{
			pmov->setShipState(1, false);
		}
		else
		{
			pmov->setShipState(1, true);
		}
		pmov->setShipState(0, false);	//don't turn right
		pmov->setShipState(3, false);	//don't move backward/break
		pmov->setShipState(4, false);	//don't fire

		if (diffLeft < 20)
		{
			pmov->setShipState(2, true);	// move forward
		}
		else
		{
			pmov->setShipState(2, false);	// don't move forward
		}
	}
	else	//turn right
	{
		if (diffRight < 3)
		{
			pmov->setShipState(0, false);
		}
		else
		{
			pmov->setShipState(0, true);
		}
		pmov->setShipState(1, false);	//don't turn left
		pmov->setShipState(2, false);	//don't move forward
		pmov->setShipState(3, false);	//don't move backward/break
		pmov->setShipState(4, false);	//don't fire
	}

	
}

