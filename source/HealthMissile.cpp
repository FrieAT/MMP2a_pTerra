/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "HealthMissile.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

HealthMissile::HealthMissile(float fHealth, GameObject* pOwner)
{
	this->m_fHealth = fHealth;
    this->m_pOwner = pOwner;
}

HealthMissile::~HealthMissile()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
}

void HealthMissile::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

void HealthMissile::Damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO add destruction effect
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
	}
}

void HealthMissile::OnFrameUpdate(sf::Time DeltaTime)
{
	this->Damage(1);
}

void HealthMissile::OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact)
{
    // Ignore Collision with Owner-Ship.
    if(pOther == m_pOwner)
    {
        return;
    }
    
    this->Damage(m_fHealth);
    
    IHealth* pOtherHealth = static_cast<IHealth*>(pOther->GetComponent(EComponentType::Health));
    if(pOtherHealth != nullptr)
    {
        pOtherHealth->Damage(90001.f); // What does the scouter say to his power level?
    }
}
