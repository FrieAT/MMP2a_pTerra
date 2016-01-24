#include "stdafx.h"

#include "AIStatePatrol.h"
#include "ShipMovement.h"
#include "IPosition.h"
#include "ObjectManager.h"
#include "IScore.h"

#define _USE_MATH_DEFINES
#include <math.h>

AIStatePatrol::AIStatePatrol()
	:m_nextAngle(90),
	m_Timer(300)
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
	m_Timer--;

	if (currentRotation > m_nextAngle - 5 && currentRotation < m_nextAngle + 5) {	//in right direction
		if (m_Timer < 0) {
			m_nextAngle = fmod(m_nextAngle + 90, 360);	//change direction
			m_Timer = 300;
		}
		else if (m_Timer>100) {		//accelarate
			pmov->setShipState(2, true);	//move forward
			pmov->setShipState(3, false);	//don't move backward
			pmov->setShipState(0, false);	//don't turn right
			pmov->setShipState(1, false);	//don't turn left
			pmov->setShipState(4, false);	//don't fire
		}
		else {		//break
			pmov->setShipState(2, false);	//don't move forward
			pmov->setShipState(3, true);	//move backward/break
			pmov->setShipState(0, false);	//don't turn right
			pmov->setShipState(1, false);	//don't turn left
			pmov->setShipState(4, false);	//don't fire
		}
	}
	else {		//in wrong direction

		float diffLeft;
		float diffRight;
		if (currentRotation < m_nextAngle)
		{
			diffLeft = currentRotation + 360 - m_nextAngle;
			diffRight = m_nextAngle - currentRotation;
		}
		else
		{
			diffLeft = currentRotation - m_nextAngle;
			diffRight = 360 - currentRotation + m_nextAngle;
		}

		if (diffLeft < diffRight)	//turn left
		{
			pmov->setShipState(2, false);	//don't move forward
			pmov->setShipState(3, false);	//don't move backward/break
			pmov->setShipState(0, false);	//don't turn right
			pmov->setShipState(1, true);	//turn left
			pmov->setShipState(4, false);	//don't fire
		}
		else	//turn right
		{
			pmov->setShipState(2, false);	//don't move forward
			pmov->setShipState(3, false);	//don't move backward/break
			pmov->setShipState(0, true);	//turn right
			pmov->setShipState(1, false);	//don't turn left
			pmov->setShipState(4, false);	//don't fire
		}
	}
}

