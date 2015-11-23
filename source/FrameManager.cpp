/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "FrameManager.h"

void FrameManager::Update(sf::Time DeltaTime)
{
    for (unsigned int i = 0; i < m_Observers.size(); i++)
    {
        m_Observers[i]->OnFrameUpdate(DeltaTime);
    }
}

void FrameManager::Draw(sf::RenderWindow* pWindow)
{
    for (unsigned int i = 0; i < m_Observers.size(); i++)
    {
        m_Observers[i]->OnFrameDraw(pWindow);
    }
}

void FrameManager::RegisterEventObserver(IFrameObserver* pObserver)
{
	m_Observers.push_back(pObserver);
}

void FrameManager::UnregisterEventObserver(IFrameObserver* pObserver)
{
    for(unsigned int i = 0; i < m_Observers.size(); i++)
    {
        if(m_Observers[i] != pObserver) continue;
        m_Observers.erase(m_Observers.begin() + i);
        break;
    }
}

void FrameManager::Clear()
{
	m_Observers.clear();
	m_Observers.shrink_to_fit();
}