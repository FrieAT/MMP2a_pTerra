/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "FrameManager.h"
#include "IComponent.h"
#include "IPosition.h"

void FrameManager::Update(sf::Time DeltaTime)
{
    // int count = 0;
    for (unsigned int i = 0; i < m_Observers.size(); i++)
    {
        IComponent* pComponent = dynamic_cast<IComponent*>(m_Observers[i]);
        // Normally a Observer of FrameManager is always a Component, but who knows the future.
        if(pComponent != nullptr)
        {
            IPosition* pPositionComponent = static_cast<IPosition*>(pComponent->GetAssignedGameObject()->GetComponent(EComponentType::Position));
            // If component has a IPosition (which is maybe always)
            if(pPositionComponent != nullptr)
            {
                // Check if current Quadrant is freezed or not.
                // if so, don´t perform OnFrameUpdate on Observer.
                Quadrant* pQuadrant = pPositionComponent->GetQuadrant();
                if(pQuadrant != nullptr && pQuadrant->GetFreezedState())
                {
                    // Skip observer call for this GameObject.
                    continue;
                }
            }
        }
        
        m_Observers[i]->OnFrameUpdate(DeltaTime);
        // count++;
    }
    
    // std::cout << "Frame Manager Update called for " << count << " Objects." << std::endl;
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