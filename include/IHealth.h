/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IHealth : public IComponent
{
public:
	EComponentType GetComponentType()
	{
		return EComponentType::Health;
	}
	float m_fHealth;
	virtual void Damage(float fDamage) = 0;
};