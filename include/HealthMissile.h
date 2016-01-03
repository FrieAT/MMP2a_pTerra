/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"
#include "ICollisionEventObserver.h"

class HealthMissile : public IHealth, public IFrameObserver, public ICollisionEventObserver
{
public:
	HealthMissile(float fHealth, GameObject* pOwner);
	~HealthMissile();
    void Init();
	void Damage(float fDamage);
	void OnFrameUpdate(sf::Time DeltaTime);
    void OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact);
    std::string GetComponentName() { return std::string("HealthMissile"); }
private:
    GameObject* m_pOwner;
};