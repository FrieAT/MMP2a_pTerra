/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "Shiphealth.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Shiphealth::Shiphealth(float fHealth)
{
	this->m_fHealth = fHealth;
	FrameManager::GetInstance().RegisterEventObserver(this);
    
}

void Shiphealth::Init()
{
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

Shiphealth::~Shiphealth()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
}



void Shiphealth:: damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO destroy Ship and remove end game
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
	}
}

void Shiphealth::OnFrameUpdate(sf::Time DeltaTime)
{
	//this->damage(1);
}

void Shiphealth::OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact)
{
    std::cout << "Detected Collision with a " << pOther->GetID() << " (Impulse: " << ImpulseImpact.x << " / " << ImpulseImpact.y << ")" << std::endl;
}
