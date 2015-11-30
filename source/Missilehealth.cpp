/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "Missilehealth.h"
#include "ObjectManager.h"

Missilehealth::Missilehealth(float fHealth)
{
	this->m_fHealth = fHealth;
	FrameManager::GetInstance().RegisterEventObserver(this);

}

Missilehealth::~Missilehealth()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
}



void Missilehealth::damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO add destruction effect
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
	}
}

void Missilehealth::OnFrameUpdate(sf::Time DeltaTime)
{
	this->damage(1);
}
