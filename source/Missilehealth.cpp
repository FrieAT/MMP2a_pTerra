/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "Missilehealth.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Missilehealth::Missilehealth(float fHealth)
{
	this->m_fHealth = fHealth;
	FrameManager::GetInstance().RegisterEventObserver(this);

}

Missilehealth::~Missilehealth()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
}

void Missilehealth::Init()
{
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

void Missilehealth::damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO add destruction effect
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
	}
}

void Missilehealth::OnFrameUpdate(sf::Time DeltaTime)
{
	this->damage(1);
}

void Missilehealth::OnCollisionEvent(GameObject *pOther, sf::Vector2f ImpulseImpact)
{
    // Destroy missile itself
    this->damage(m_fHealth);
    
    // Check for a Health-Component for pOther-GameObject
    IHealth* pOtherHealth = static_cast<IHealth*>(pOther->GetComponent(EComponentType::Health));
    if(pOtherHealth != nullptr)
    {
        pOtherHealth->damage(90001.f); // What does the scouter say to his power level?
    }
}
