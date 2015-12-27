/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "ObjectManager.h"
#include "IPosition.h"

ObjectManager::ObjectManager()
{
	m_DrawOrder = std::vector<std::string> { "background", "asteroid", "missile", "ship", "text" };
}

std::pair<std::string, Quadrant*> ObjectManager::GetKeyFromGameObject(GameObject *pGameObject)
{
    if(pGameObject == nullptr)
    {
        throw std::runtime_error("Given GameObject-object has a null-pointer-reference.");
    }
    
    Quadrant* pQuadrantFromObject = nullptr;
    std::string strGameObjectID = pGameObject->GetID();
    
    IPosition* pPositionComponent = static_cast<IPosition*>(pGameObject->GetComponent(EComponentType::Position));
    if(pPositionComponent != nullptr)
    {
        pQuadrantFromObject = pPositionComponent->GetQuadrant();
    }
    
    return std::pair<std::string, Quadrant*>(strGameObjectID, pQuadrantFromObject);
}

std::pair<std::string, Quadrant*> ObjectManager::GetKeyFromIDAndQuadrant(std::string object_id, Quadrant* pQuadrant)
{
    return std::pair<std::string, Quadrant*>(object_id, pQuadrant);
}

void ObjectManager::AddGameObject(GameObject* pObject)
{
    if(pObject == nullptr)
    {
        throw std::runtime_error("Given GameObject-object has a null-pointer-reference.");
    }
    m_Objects[GetKeyFromGameObject(pObject)].push_back(pObject);
}

void ObjectManager::RemoveGameObject(GameObject* pObject)
{
    if(pObject == nullptr)
    {
        throw std::runtime_error("Given GameObject-object has a null-pointer-reference.");
    }
    auto key = GetKeyFromGameObject(pObject);
    auto i = m_Objects[key].begin();
    while(i != m_Objects[key].end())
	{
		if (*i != pObject)
		{
			i++;
			continue;
		}
		else
		{
			m_CleanUp.push_back(*i);
			m_Objects[key].erase(i);
			break;
		}
	}
}

void ObjectManager::RemoveAllGameObjects()
{
    auto it = m_Objects.begin();
    while(it != m_Objects.end())
    {
        if (it->second.size() == 0)
        {
            continue;
        }
        
        auto vec_it = it->second.begin();
        while(vec_it != it->second.end())
        {
            delete((*vec_it));
            vec_it++;
        }
        it->second.clear();
        it++;
    }
    m_Objects.clear();
}

void ObjectManager::AddQuadrant(Quadrant *pChunk)
{
    if(pChunk == nullptr)
    {
        throw std::runtime_error("Given Quadrant-object has a null-pointer-reference.");
    }
    auto key = pChunk->GetIndex();
    // Handling if Index ist not unique will be checked in WorldManager.
    m_Quadrants[key] = pChunk;
}

void ObjectManager::RemoveQuadrant(Quadrant *pChunk)
{
    if(pChunk == nullptr)
    {
        throw std::runtime_error("Given Quadrant-object has a null-pointer-reference.");
    }
    auto key = pChunk->GetIndex();
    m_Quadrants.erase(key);
}

void ObjectManager::RemoveAllQuadrants()
{
    m_Quadrants.clear(); // Quadrant-Removing handles the WorldManager itself.
}

void ObjectManager::Update(sf::Time DeltaTime)
{
	// Get rid of obsolete Gameobjects
	for (int i = 0; i < m_CleanUp.size(); i++)
	{
		delete m_CleanUp[i];
	}
	m_CleanUp.clear();
}

void ObjectManager::Draw(sf::RenderWindow* pWindow)
{
    // std::vector Iteratores to perform after the Loop
    std::vector<std::pair<std::pair<std::string, Quadrant*>, std::vector<GameObject*>::iterator>> RemoveGameObjectsFromList;
    std::vector<std::pair<int, int>> RemoveQuadrantFromList;
    
    // Iterate through all DrawOrder´s
    auto draw_order_it = m_DrawOrder.begin();
	while(draw_order_it != m_DrawOrder.end())
	{
        // Iterate through all registered Quadrant´s to be active.
        auto quadrant_it = m_Quadrants.begin();
        while(quadrant_it != m_Quadrants.end())
        {
            // Check from Quadrant within, if it is in a Freezed-State.
            if(!quadrant_it->second->GetFreezedState())
            {
                // Iterate now through all GameObjects with given GameObjectID and Quadrant-Position.
                auto key = GetKeyFromIDAndQuadrant((*draw_order_it), (quadrant_it->second));
                auto objects_it = m_Objects[key].begin();
                while(objects_it != m_Objects[key].end())
                {
                    // Check if GameObject is in right Quadrant
                    // (Could be, if GameObject moved to other Quadrant, and isn´t deleted from List due of inefficient performance)
                    IPosition* pPosition = static_cast<IPosition*>((*objects_it)->GetComponent(EComponentType::Position));
                    if(pPosition != nullptr)
                    {
                        if(pPosition->GetQuadrant() != quadrant_it->second)
                        {
                            auto value = std::pair<std::pair<std::string, Quadrant*>, std::vector<GameObject*>::iterator>(key, objects_it);
                            RemoveGameObjectsFromList.push_back(value);
                            objects_it++;
                            continue;
                        }
                    }
                    
                    // Check if GameObject has a IDrawing-Component.
                    IDrawing* pDrawing = static_cast<IDrawing*>((*objects_it)->GetComponent(EComponentType::Drawing));
                    if (pDrawing != nullptr)
                    {
                        pDrawing->Draw(pWindow);
                    }
                    objects_it++;
                }
            }
            else
            {
                // Maybe if Quadrant is really in freezed state (due of a bug), remove it from the List.
                RemoveQuadrantFromList.push_back(quadrant_it->first);
            }
            quadrant_it++;
        }
        draw_order_it++;
	}
    
    // Clear unneccessary GameObjects from List.
    auto it_rest_objects = RemoveGameObjectsFromList.begin();
    while(it_rest_objects != RemoveGameObjectsFromList.end())
    {
        // m_Objects[it_rest_objects->first].erase(it_rest_objects->second);
        it_rest_objects++;
    }
    
    // Clear unneccessary Quadrants from List.
    auto it_rest_quadrants = RemoveQuadrantFromList.begin();
    while(it_rest_quadrants != RemoveQuadrantFromList.end())
    {
        // m_Quadrants.erase((*it_rest_quadrants));
        it_rest_quadrants++;
    }
}

void ObjectManager::Clear()
{
    RemoveAllGameObjects();
    RemoveAllQuadrants();

	m_DrawOrder.clear();
	m_DrawOrder.shrink_to_fit();
}