/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include "Shiphealth.h"
#include "ObjectManager.h"

Shiphealth::Shiphealth(float fHealth)
{
	this->m_fHealth = fHealth;
	FrameManager::GetInstance().RegisterEventObserver(this);

}

Shiphealth::~Shiphealth()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
}



void Shiphealth:: damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO destroy Ship and remove end game
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
	}
}

void Shiphealth::OnFrameUpdate(sf::Time DeltaTime)
{
	//this->damage(1);
}