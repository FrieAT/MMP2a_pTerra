/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "IHealth.h"
#include "IFrameObserver.h"
#include "FrameManager.h"

class Shiphealth : public IHealth , public IFrameObserver
{
public:
	Shiphealth(float fHealth);
	~Shiphealth();
	void damage(float fDamage);
	void OnFrameUpdate(sf::Time DeltaTime);
};