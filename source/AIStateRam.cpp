#include "stdafx.h"

#include "AIStateRam.h"
#include "ShipMovement.h"
#include "IPosition.h"
#include "ObjectManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

AIStateRam::AIStateRam()
{
}


AIStateRam::~AIStateRam()
{
}

void AIStateRam::Update(GameObject* obj)
{
	IPosition* ppos = static_cast<IPosition*>(obj->GetComponent(EComponentType::Position));
	ShipMovement* pmov = static_cast<ShipMovement*>(obj->GetComponent(EComponentType::Movement));

	// Get current rotation
	float currentRotation = ppos->GetRotation();

	// Get vector from AI ship to player ship
	IPosition* pPlayerPos = static_cast<IPosition*>(ObjectManager::GetInstance().GetPlayer()->GetComponent(EComponentType::Position));
	sf::Vector2f diff = pPlayerPos->GetPosition() - ppos->GetPosition();
	float diffRotation = std::fmodf((std::atan2f(diff.y, diff.x) * 180.f / M_PI + 450), 360.f);
	
	float diffLeft;
	float diffRight;
	if (currentRotation < diffRotation)
	{
		diffLeft = currentRotation + 360 - diffRotation;
		diffRight = diffRotation - currentRotation;
	}
	else
	{
		diffLeft = currentRotation - diffRotation;
		diffRight = 360 - currentRotation + diffRotation;
	}

	if (diffLeft < diffRight) // turn left
	{
		// avoid jittery behavior with rotation (trying to get exact angle)
		if (diffLeft < 10)
		{
			pmov->setShipState(1, false);
		}
		else
		{
			pmov->setShipState(1, true);
		}
		pmov->setShipState(0, false); // don't turn right

		// Only fire when enemy in front of ship
		if (diffLeft < 20)
		{
			pmov->setShipState(2, true); // move forward
			pmov->setShipState(4, true); // shoot
		}
		else
		{
			pmov->setShipState(2, false); // don't move forward
			pmov->setShipState(4, false); // don't shoot
		}
	}
	else // turn right
	{
		// avoid jittery behavior with rotation (trying to get exact angle)
		if (diffRight < 10)
		{
			pmov->setShipState(0, false);
		}
		else
		{
			pmov->setShipState(0, true);
		}
		pmov->setShipState(1, false); // turn left
		pmov->setShipState(2, true); // move forward
		
		// Only fire when enemy in front of ship
		if (diffRight < 20)
		{
			pmov->setShipState(2, true); // move forward
			pmov->setShipState(4, true); // shoot
		}
		else
		{
			pmov->setShipState(2, false); // don't move forward
			pmov->setShipState(4, false); // don't shoot
		}
	}
}
