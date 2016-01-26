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

	if (diffLeft < diffRight)
	{
		pmov->setShipState(1, true);
		pmov->setShipState(0, false);
		pmov->setShipState(2, true);
		pmov->setShipState(4, true);

	}
	else
	{
		pmov->setShipState(0, true);
		pmov->setShipState(1, false);
		pmov->setShipState(2, true);
		pmov->setShipState(4, true);

	}
}
