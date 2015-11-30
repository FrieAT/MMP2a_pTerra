/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"

class Missilehealth : public IHealth, public IFrameObserver
{
public:
	Missilehealth(float fHealth);
	~Missilehealth();
	void damage(float fDamage);
	void OnFrameUpdate(sf::Time DeltaTime);
};