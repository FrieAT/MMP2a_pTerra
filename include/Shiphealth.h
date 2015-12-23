/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"
#include "ICollisionEventObserver.h"

class Shiphealth : public IHealth , public IFrameObserver, public ICollisionEventObserver
{
public:
	Shiphealth(float fHealth);
	~Shiphealth();
    void Init();
	void damage(float fDamage);
	void OnFrameUpdate(sf::Time DeltaTime);
    void OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact);
};