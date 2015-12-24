/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"
#include "ICollisionEventObserver.h"

class Missilehealth : public IHealth, public IFrameObserver, public ICollisionEventObserver
{
public:
	Missilehealth(float fHealth);
	~Missilehealth();
    void Init();
	void damage(float fDamage);
	void OnFrameUpdate(sf::Time DeltaTime);
    void OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact);
};