/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "ObjectManager.h"
#include "IPosition.h"
#include "WorldManager.h"

ObjectManager::ObjectManager()
{
	m_DrawOrder = std::vector<std::string> { "background", "planet", "asteroid", "missile", "enemyship", "ship", "space_station", "text", "effect", "screen" };
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
    auto key = GetKeyFromGameObject(pObject);
	
	// Check if game object already exists in this quadrant
	// NOTE: Yes it only checks the given quadrant from the game object. if the game object is added twice to a quadrant, to which it isn´t defined
	// so the ObjectManager will erase the wrong entry in the draw-cycle.
    auto objects_it = m_Objects[key].begin();
    while(objects_it != m_Objects[key].end())
    {
        if((*objects_it) == pObject)
        {
            throw std::runtime_error("GameObject already in List.");
        }
        objects_it++;
    }
	
    m_Objects[key].push_back(pObject);
}

void ObjectManager::RemoveGameObject(GameObject* pObject, bool bDelete)
{
    if(pObject == nullptr)
    {
        throw std::runtime_error("Given GameObject-object has a null-pointer-reference.");
    }
    if(bDelete && pObject->GetAssistedState())
    {
        // Ignore Deletion, if it is a assisted game object.
        // This can be caused, if GameState-Changes or GameWindow closes
        // If so, it may be possible that AssistedGameObject will be deleted before the Owner from this Object
        // when this occurs, the destructor in the Owner will try to delete the AssistedGameObject again
        // and a BAD_ACCESS_EXCEPTION occurs.
        return;
    }
    auto key = GetKeyFromGameObject(pObject);
    auto i = m_Objects[key].begin();
    while(i != m_Objects[key].end())
	{
		if ((*i) != pObject)
		{
			i++;
			continue;
		}
		else
		{
			if (bDelete)
			{
				m_CleanUp.push_back((*i));
			}
			m_Objects[key].erase(i);
			break;
		}
	}
	if (!pObject->IsInFreezedState())
	{
		auto active_it = m_ActiveGameObjects.begin();
		while (active_it != m_ActiveGameObjects.end())
		{
			if ((*active_it) == pObject)
			{
				// It is not possible to erase-Element, because it could destroy the iterator´s which accesses to m_ActiveGameObjects
				// However if it is set to nullptr, it is only in one frame there. In the next frame it won´t show up again, as it is removed
				// from m_Objects
				(*active_it) = nullptr;
				break;
			}
			active_it++;
		}
	}
}

void ObjectManager::RemoveAllGameObjects()
{
    std::vector<GameObject*> EreasedGameObjects;
    
    // ATTENTION: This is not to be meant there, but somehow there is something in the loop which causes to break the program flow without exception or error. This only fix here Problems with other GameStates as it will be just overwritten.
    // But the problem here causes a memory leak, because not all objects get deleted.
    // This problem will focused later.
    m_ActiveGameObjects.clear();
    
    auto it = m_Objects.begin();
    while(it != m_Objects.end())
    {
        if (it->second.size() == 0)
        {
            it++;
            continue;
        }
        
        auto vec_it = it->second.begin();
        while(vec_it != it->second.end())
        {
			if ((*vec_it) == nullptr)
			{
				vec_it++;
				continue;
			}
            if((*vec_it)->GetAssistedState())
            {
                // Ignore Deletion, if it is a assisted game object.
                // This can be caused, if GameState-Changes or GameWindow closes
                // If so, it may be possible that AssistedGameObject will be deleted before the Owner from this Object
                // when this occurs, the destructor in the Owner will try to delete the AssistedGameObject again
                // and a BAD_ACCESS_EXCEPTION occurs.
                return;
            }
            bool already_ereased = false;
            auto check_it = EreasedGameObjects.begin();
            while(check_it != EreasedGameObjects.end())
            {
                if((*check_it) == (*vec_it))
                {
                    already_ereased = true;
                    break;
                }
                check_it++;
            }
            if(!already_ereased)
            {
                auto check_cleanup_it = m_CleanUp.begin();
                while(check_cleanup_it != m_CleanUp.end())
                {
                    if((*check_cleanup_it) == (*vec_it))
                    {
                        already_ereased = true;
                        break;
                    }
                    check_cleanup_it++;
                }
            }
            if(!already_ereased)
            {
                // TODO: Fix maybe possible heap corruption.
                if((*vec_it)->GetAmountOfUsedComponentTypes() > 0 && (*vec_it)->GetAmountOfUsedComponentTypes() <= (int)EComponentType::MaxItem)
                {
                    delete((*vec_it));
                }
                EreasedGameObjects.push_back((*vec_it));
            }
            vec_it++;
        }
        it->second.clear();
        it++;
    }
    PerformGameObjectCleanUp();
    m_Objects.clear();
    EreasedGameObjects.clear();
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

void ObjectManager::PerformGameObjectCleanUp()
{
    // Get rid of obsolete Gameobjects
    for (unsigned int i = 0; i < m_CleanUp.size(); i++)
    {
        delete m_CleanUp[i];
    }
    m_CleanUp.clear();
}

void ObjectManager::Update(sf::Time DeltaTime)
{
    PerformGameObjectCleanUp();
}

void ObjectManager::Draw(sf::RenderWindow* pWindow)
{
    // Clear old active GameObjects, as it will be generated new.
    m_ActiveGameObjects.clear();
    
    // std::vector Iteratores to perform after the Loop
    std::vector<std::pair<std::pair<std::string, Quadrant*>, int>> RemoveGameObjectsFromList;
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
                    IPosition* pPosition = nullptr;
                    if((*objects_it) != nullptr || ((*objects_it)->GetID()).length() > 0)
                    {
                        pPosition = static_cast<IPosition*>((*objects_it)->GetComponent(EComponentType::Position));
                    }
                    if((*objects_it) == nullptr || (pPosition != nullptr && pPosition->GetQuadrant() != quadrant_it->second))
                    {
                        //std::cout << "Removing (" << (objects_it - m_Objects[key].begin()) << ") " << (*objects_it)->GetID() << " from ListQuadrant " << (quadrant_it->second->GetIndex()).first << " / " << (quadrant_it->second->GetIndex()).second << std::endl;
                        auto value = std::pair<std::pair<std::string, Quadrant*>, int>(key, objects_it - m_Objects[key].begin());
                        RemoveGameObjectsFromList.push_back(value);
                        objects_it++;
                        continue;
                    }
                    
                    // Check if GameObject has a IDrawing-Component.
                    IDrawing* pDrawing = static_cast<IDrawing*>((*objects_it)->GetComponent(EComponentType::Drawing));
                    if (pDrawing != nullptr)
                    {
                        pDrawing->Draw(pWindow);
                    }
                    
                    // Add GameObject to current ActiveGameObject list
                    m_ActiveGameObjects.push_back((*objects_it));
                    
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
    for(int i = (RemoveGameObjectsFromList.size()-1); i >= 0; i--)
    {
        auto value = RemoveGameObjectsFromList[i];
        auto key = value.first;
        auto it_game_object = value.second;
        std::cout << "Try to delete obect at index " << (it_game_object) << " with id " << key.first << " in Quadrant " << (key.second->GetIndex()).first << " / " << (key.second->GetIndex()).second << " !" << std::endl;
        m_Objects[key].erase(m_Objects[key].begin() + it_game_object);
    }
    
    // Clear unneccessary Quadrants from List.
    auto it_rest_quadrants = RemoveQuadrantFromList.begin();
    while(it_rest_quadrants != RemoveQuadrantFromList.end())
    {
        m_Quadrants.erase((*it_rest_quadrants));
        it_rest_quadrants++;
    }
}

void ObjectManager::Clear()
{
    RemoveAllGameObjects();
    RemoveAllQuadrants(); 
}

std::vector<GameObject*> ObjectManager::GetActiveGameObjects()
{
    return m_ActiveGameObjects;
}