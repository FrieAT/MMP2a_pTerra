/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "HealthMissile.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "GameObjectFactory.h"
#include "INavigation.h"
#include "WorldManager.h"

HealthMissile::HealthMissile(float fHealth, GameObject* pOwner)
{
	this->m_fHealth = fHealth;
    this->m_pOwner = pOwner;
    this->m_bSomethingHitted = false;
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
    if(pOther == m_pOwner)
    {
        return;
    }
    
    m_bSomethingHitted = true;
    this->Damage(m_fHealth);
    
    // Generate Explosion, if other gameobject has a IPosition (i know, what a question).
    IPosition* pPositionComponent = static_cast<IPosition*>(pOther->GetComponent(EComponentType::Position));
    if(pPositionComponent != nullptr)
    {
        GameObjectFactory::CreateExplosion(pPositionComponent->GetPosition());
    }
    
    IHealth* pOtherHealth = static_cast<IHealth*>(pOther->GetComponent(EComponentType::Health));
    if(pOtherHealth != nullptr)
    {
        pOtherHealth->Damage(90001.f); // What does the scouter say to his power level?
        
        // Only set Navigation point to next nearest space station, if something with Health is destroyed.
        if(m_pOwner != nullptr)
        {
            IPosition* pPositionOwner = static_cast<IPosition*>(m_pOwner->GetComponent(EComponentType::Position));
            INavigation* pNavigationOwner = static_cast<INavigation*>(m_pOwner->GetComponent(EComponentType::Navigation));
            if(pNavigationOwner != nullptr)
            {
                sf::Vector2f NextCoords = WorldManager::GetInstance().GetNextNearestObjectPos(pPositionOwner->GetPosition());
                pNavigationOwner->SetNavigationPoint(NextCoords);
                pNavigationOwner->SetNavigationActive(true);
            }
        }
    }
}

IComponent* HealthMissile::Deserialize(SerializeNode *pNode)
{
    // TODO: Don´t create missile after Savegame-Load, cuz Reference to its owner is loss.
    HealthMissile* pComponent = new HealthMissile(0.f, nullptr); // Only properties from own class, should be handled in Deserialize!
    
    IHealth::Deserialize(pNode, pComponent);
    
    return pComponent;
}