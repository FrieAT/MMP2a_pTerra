/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "FrameManager.h"
#include "IComponent.h"
#include "ObjectManager.h"

void FrameManager::Update(sf::Time DeltaTime)
{
    std::vector<GameObject*> CurrentGameObjects = ObjectManager::GetInstance().GetActiveGameObjects();
    for (unsigned int i = 0; i < CurrentGameObjects.size(); i++)
    {
        // Check if the GameObject has components which are registered to the FrameManager.
        auto key = CurrentGameObjects[i];
        if(m_Observers[key].size() == 0)
        {
            continue;
        }
        
        // Check if Observer is a IComponent and check from GameObject within, if it is in a Freezed-State.
        if(CurrentGameObjects[i]->IsInFreezedState())
        {
            continue;
        }
        
        auto it = m_Observers[key].begin();
        while(it != m_Observers[key].end())
        {
            (*it)->OnFrameUpdate(DeltaTime);
            it++;
        }
        // count++;
    }
    
    // std::cout << "Frame Manager Update called for " << count << " Objects." << std::endl;
}

void FrameManager::Draw(sf::RenderWindow* pWindow)
{
    std::vector<GameObject*> CurrentGameObjects = ObjectManager::GetInstance().GetActiveGameObjects();
    for (unsigned int i = 0; i < CurrentGameObjects.size(); i++)
    {
        // Check if the GameObject has components which are registered to the FrameManager.
        auto key = CurrentGameObjects[i];
        if(m_Observers[key].size() == 0)
        {
            continue;
        }
        
        // Check if Observer is a IComponent and check from GameObject within, if it is in a Freezed-State.
        if(CurrentGameObjects[i]->IsInFreezedState())
        {
            continue;
        }
        
        auto it = m_Observers[key].begin();
        while(it != m_Observers[key].end())
        {
            (*it)->OnFrameDraw(pWindow);
            it++;
        }
    }
}

void FrameManager::RegisterEventObserver(IFrameObserver* pObserver)
{
    IComponent* pComponent = dynamic_cast<IComponent*>(pObserver);
    if(pComponent == nullptr)
    {
        throw std::runtime_error("Given Observer is not a IComponent.");
    }
	m_Observers[pComponent->GetAssignedGameObject()].push_back(pObserver);
}

void FrameManager::UnregisterEventObserver(IFrameObserver* pObserver)
{
    IComponent* pComponent = dynamic_cast<IComponent*>(pObserver);
    if(pComponent == nullptr)
    {
        throw std::runtime_error("Given Observer is not a IComponent.");
    }
    auto key = pComponent->GetAssignedGameObject();
    auto it = m_Observers[key].begin();
    while(it != m_Observers[key].end())
    {
        if((*it) != pObserver)
        {
            it++;
            continue;
        }
        m_Observers[key].erase(it);
        break;
    }
    if(m_Observers[key].size() <= 0)
    {
        m_Observers.erase(key);
    }
}

void FrameManager::Clear()
{
    auto it = m_Observers.begin();
    while(it != m_Observers.end())
    {
        it->second.clear();
        it++;
    }
	m_Observers.clear();
}