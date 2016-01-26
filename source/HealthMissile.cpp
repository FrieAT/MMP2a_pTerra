/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "HealthMissile.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "GameObjectFactory.h"
#include "IScore.h"
#include "ScoreEvent.h"

HealthMissile::HealthMissile(float fHealth, GameObject* pOwner)
: IHealth()
{
	this->m_fHealth = fHealth;
    this->m_pOwner = pOwner;
    this->m_bSomethingHitted = false;
    this->m_bMadeAction = false;
}

HealthMissile::~HealthMissile()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
}

void HealthMissile::Init()
{
    IHealth::Init();
    FrameManager::GetInstance().RegisterEventObserver(this);
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

void HealthMissile::Damage(float fDamage)
{
	IHealth::Damage(fDamage);
	if (m_fHealth <= 0.f)
	{
        // Generate Explosion if a IPosition exists and hasn´t hitted anything.
        if(!m_bSomethingHitted)
        {
            IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
            if(pPositionComponent != nullptr)
            {
                GameObjectFactory::CreateExplosion(pPositionComponent->GetPosition());
            }
        }
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
	if (pOther == m_pOwner || m_bMadeAction)
    {
        return;
    }
    
    IHealth* pOtherHealth = static_cast<IHealth*>(pOther->GetComponent(EComponentType::Health));
    if(pOtherHealth != nullptr)
    {
		m_bSomethingHitted = true;
		this->Damage(m_fHealth);

		// Generate Explosion, if other gameobject has a IPosition (i know, what a question).
		IPosition* pPositionComponent = static_cast<IPosition*>(pOther->GetComponent(EComponentType::Position));
		if (pPositionComponent != nullptr)
		{
			GameObjectFactory::CreateExplosion(pPositionComponent->GetPosition());
		}
		
		// Set damage for the explosion
		float dmg = 60.f;
    
		// Get for the Owner of the Missile the ResearchPoints from the Victim if he's destroyed
		if (m_pOwner != nullptr && pOtherHealth->GetHealth() - dmg <= 0)
		{
			IScore* pScoreVictim = static_cast<IScore*>(pOther->GetComponent(EComponentType::Score));
			IScore* pScoreOwner = static_cast<IScore*>(m_pOwner->GetComponent(EComponentType::Score));
			if (pScoreOwner != nullptr && pScoreVictim != nullptr)
			{
				pScoreOwner->AddScore(pScoreVictim->GetScore());
			}
		}

		// Apply the damage
		pOtherHealth->Damage(dmg);
	}
    
    m_bMadeAction = true;
}

IComponent* HealthMissile::Deserialize(SerializeNode *pNode)
{
    // TODO: Don´t create missile after Savegame-Load, cuz Reference to its owner is loss.
    HealthMissile* pComponent = new HealthMissile(0.f, nullptr); // Only properties from own class, should be handled in Deserialize!
    
    IHealth::Deserialize(pNode, pComponent);
    
    return pComponent;
}