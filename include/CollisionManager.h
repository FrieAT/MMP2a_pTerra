/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include "ICollision.h"
#include "ICollisionEventObserver.h"
#include <stack>

class CollisionManager
{
public:
	static CollisionManager& GetInstance()
	{
		static CollisionManager g_Instance;
		return g_Instance;
	}
	void Update(sf::Time DeltaTime);
	void HandleCollisions();
	void RegisterCollisionbody(ICollision* pCollisionBody);
	void UnregisterCollisionbody(ICollision* pCollisionBody);
    void RegisterCollisionEvent(ICollisionEventObserver* pThisComponent, GameObject* pGameObject);
    void UnregisterCollisionEvent(ICollisionEventObserver* pThisComponent, GameObject* pGameObject);
	void Clear();
    std::stack<CollisionEvent> m_CollisonEvents;
private:
	CollisionManager() { }
	CollisionManager(const CollisionManager&) = delete;
	void operator= (const CollisionManager&) = delete;
	std::map<ICollision*, bool> m_Colliders;
    std::map<GameObject*, bool> m_ActiveGameObjects;
    std::map<GameObject*, std::vector<ICollisionEventObserver*>> m_CollisionEventObservers;
};
