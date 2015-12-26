/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_DrawOrder = std::vector<std::string> { "background", "asteroid", "missile", "ship", "text" };
}

void ObjectManager::AddGameObject(GameObject* pObject)
{
	m_Objects[pObject->GetID()].push_back(pObject);
}

void ObjectManager::RemoveGameObject(GameObject* pObject)
{
	std::string id = pObject->GetID();
    auto i = m_Objects[id].begin();
    while(i != m_Objects[id].end())
	{
		if (*i != pObject)
		{
			i++;
			continue;
		}
		else
		{
			m_CleanUp.push_back(*i);
			m_Objects[id].erase(i);
			break;
		}
	}
}

void ObjectManager::RemoveAllGameObjects()
{
	for (unsigned int s = 0; s < ObjectManager::m_DrawOrder.size(); s++)
	{
		std::string* pDrawOrderType = &ObjectManager::m_DrawOrder[s];
		
		if (ObjectManager::m_Objects[*pDrawOrderType].size() == 0)
		{
			continue;
		}

		for (unsigned int i = 0; i < ObjectManager::m_Objects[*pDrawOrderType].size(); ++i)
		{
			delete ObjectManager::m_Objects[*pDrawOrderType][i];
		}
		ObjectManager::m_Objects[*pDrawOrderType].clear();
	}
	ObjectManager::m_Objects.clear();
}

void ObjectManager::Update(sf::Time DeltaTime)
{
	// Get rid of obsolete Gameobjects
	for (int i = 0; i < m_CleanUp.size(); i++)
	{
		delete m_CleanUp[i];
	}
	m_CleanUp.clear();

	// Update function for each object?
	// Things like health, shield regenaration, ...
}

void ObjectManager::Draw(sf::RenderWindow* pWindow)
{
	for (unsigned int s = 0; s < ObjectManager::m_DrawOrder.size(); s++)
	{
		std::string* pDrawOrderType = &ObjectManager::m_DrawOrder[s];
		for (unsigned int i = 0; i < ObjectManager::m_Objects[*pDrawOrderType].size(); i++)
		{
            // Check from GameObject within, if it is in a Freezed-State.
            if(m_Objects[*pDrawOrderType][i]->IsInFreezedState())
            {
                continue;
            }
            
            // Check if GameObject has a IDrawing-Component.
			IDrawing* pDrawing = static_cast<IDrawing*>(m_Objects[*pDrawOrderType][i]->GetComponent(EComponentType::Drawing));
			if (pDrawing == nullptr)
			{
				continue;
			}
			pDrawing->Draw(pWindow);
		}
	}
}

void ObjectManager::Clear()
{
	m_Objects.clear();

	m_DrawOrder.clear();
	m_DrawOrder.shrink_to_fit();
}