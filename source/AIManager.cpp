/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "AIManager.h"

void AIManager::RegisterAIObserver(IAIObserver* pObserver)
{
	m_Observers.push_back(pObserver);
}

void AIManager::UnregisterAIObserver(IAIObserver* pObserver)
{
	for (unsigned int i = 0; i < m_Observers.size(); i++)
	{
		if (m_Observers[i] != pObserver) continue;
		m_Observers.erase(m_Observers.begin() + i);
		break;
	}
}

void AIManager::Update(sf::Time DeltaTime)
{
	for (unsigned int i = 0; i < m_Observers.size(); i++)
	{
		m_Observers[i]->Update();
	}
}

void AIManager::Clear()
{
	m_Observers.clear();
	m_Observers.shrink_to_fit();
}

