/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "ICollision.h"
#include "ICollisionEventObserver.h"

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
	bool IsObjectActive(GameObject* pObject);
	void Clear();
    std::stack<CollisionEvent> m_CollisonEvents;
private:
	CollisionManager() { }
	CollisionManager(const CollisionManager&) = delete;
	void operator= (const CollisionManager&) = delete;
	std::unordered_map<ICollision*, bool> m_Colliders;
    std::unordered_map<GameObject*, bool> m_ActiveGameObjects;
    std::unordered_map<GameObject*, std::vector<ICollisionEventObserver*>> m_CollisionEventObservers;
};
