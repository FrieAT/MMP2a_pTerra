/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "IHealth.h"

class Shiphealth : public IHealth
{
public:
	Shiphealth(float fHealth);
	~Shiphealth();
	void damage(float fDamage);
};