/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "CircleCollision.h"
#include "CollisionManager.h"

#include <iostream>

CircleCollision::CircleCollision(float fRadius,IPosition* pPosition)
	:m_pPosition(pPosition)
	,m_fRadius(fRadius)
{

}

CircleCollision::~CircleCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
	FrameManager::GetInstance().UnregisterEventObserver(this);

}

void CircleCollision::Init()
{
    CollisionManager::GetInstance().RegisterCollisionbody(this);
    FrameManager::GetInstance().RegisterEventObserver(this);
}

bool CircleCollision::colliding(ICollision* pCollisionBody)
{
	CircleCollision* pOther = static_cast<CircleCollision*> (pCollisionBody);

	sf::Vector2f lenght_vec = pOther->m_pPosition->GetPosition() - m_pPosition->GetPosition();
	
	float fLength = lenght_vec.x*lenght_vec.x + lenght_vec.y*lenght_vec.y;
	float fDistance = m_fRadius + pOther->m_fRadius;
	fDistance = fDistance*fDistance;

	if (fLength < fDistance)
	{
		m_bHit = true;
		CollisionEvent col_ev;
		col_ev.Body1 = this->GetAssignedGameObject();
		col_ev.Body2 = pOther->GetAssignedGameObject();
		col_ev.normal =  -(lenght_vec/4.f); 
		CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);
		return true;
	}
	else
	{
		m_bHit = false;
		return false;
	}
}

void CircleCollision::OnFrameDraw(sf::RenderWindow* pWindow)
{
    /*
	sf::CircleShape test(radius);
	if(hit) test.setFillColor(sf::Color::Magenta);
	else test.setFillColor(sf::Color::Blue);
	test.setPosition(pos->GetPosition()- sf::Vector2f(radius, radius));
	
	//pWindow->draw(test);
     */
}
