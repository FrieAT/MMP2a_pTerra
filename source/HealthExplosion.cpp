/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "HealthExplosion.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Game.h"

HealthExplosion::HealthExplosion(float fHealth)
: IHealth()
{
    this->m_fHealth = fHealth;
	SoundManager::GetInstance().PlaySoundExplosion();
}

HealthExplosion::~HealthExplosion()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void HealthExplosion::Init()
{
    IHealth::Init();
    FrameManager::GetInstance().RegisterEventObserver(this);
}

void HealthExplosion::Damage(float fDamage)
{
    IHealth::Damage(fDamage);
    if (m_fHealth <= 0.f)
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
    // NOTE: Don´t create missile after Savegame-Load, cuz Reference to its owner is loss.
    HealthExplosion* pComponent = new HealthExplosion(0.f); // Only properties from own class, should be handled in Deserialize!
    
    IHealth::Deserialize(pNode, pComponent);
    
    return pComponent;
}