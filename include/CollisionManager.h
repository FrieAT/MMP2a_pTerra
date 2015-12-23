/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include "ICollision.h"
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
	void RegisterCollisionbody(ICollision* Collisionbody);
	void UnregisterCollisionbody(ICollision* Collisionbody);
	void Clear();
	std::stack<CollisionEvent> m_CollisonEvents;

private:
	CollisionManager() { }
	CollisionManager(const CollisionManager&) = delete;
	void operator= (const CollisionManager&) = delete;
	std::vector<ICollision*> m_Colliders;
};
