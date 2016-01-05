/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "HealthExplosion.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Game.h"

HealthExplosion::HealthExplosion(float fHealth)
{
    this->m_fHealth = fHealth;
}

HealthExplosion::~HealthExplosion()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void HealthExplosion::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
}

void HealthExplosion::Damage(float fDamage)
{
    m_fHealth -= fDamage;
    if (m_fHealth < 0)
    {
        ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
    }
}

void HealthExplosion::OnFrameUpdate(sf::Time DeltaTime)
{
    this->Damage(1.f / Game::m_iFrameRate);
}

IComponent* HealthExplosion::Deserialize(SerializeNode *pNode)
{
    // TODO: Don´t create missile after Savegame-Load, cuz Reference to its owner is loss.
    HealthExplosion* pComponent = new HealthExplosion(0.f); // Only properties from own class, should be handled in Deserialize!
    
    IHealth::Deserialize(pNode, pComponent);
    
    return pComponent;
}