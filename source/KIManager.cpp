#include "KIManager.h"


void KIManager::RegisterKIObserver(IKIObserver* pObserver)
{
	m_Observers.push_back(pObserver);
}

void KIManager::UnregisterKIObserver(IKIObserver* pObserver)
{
	for (unsigned int i = 0; i < m_Observers.size(); i++)
	{
		if (m_Observers[i] != pObserver) continue;
		m_Observers.erase(m_Observers.begin() + i);
		break;
	}
}

void KIManager::Update(sf::Time DeltaTime)
{
	for (unsigned int i = 0; i < m_Observers.size(); i++)
	{
		m_Observers[i]->Update();
	}
}

void KIManager::Clear()
{
	m_Observers.clear();
	m_Observers.shrink_to_fit();
}

