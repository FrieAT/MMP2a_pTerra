/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "Shiphealth.h"

Shiphealth::Shiphealth(float fHealth)
{
	this->m_fHealth = fHealth;
}

Shiphealth::~Shiphealth()
{}



void Shiphealth:: damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO destroy Ship and remove
		
	}
}