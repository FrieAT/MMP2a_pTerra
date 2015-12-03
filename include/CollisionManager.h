/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include "ICollision.h"

class CollisionManager
{
public:
	static CollisionManager& GetInstance()
	{
		static CollisionManager g_Instance;
		return g_Instance;
	}
	void Update(sf::Time DeltaTime);
	void RegisterCollisionbody(ICollision* Collisionbody);
	void UnregisterCollisionbody(ICollision* Collisionbody);
	void clear();
private:
	CollisionManager() { }
	CollisionManager(const CollisionManager&) = delete;
	void operator= (const CollisionManager&) = delete;
	std::vector<ICollision*> m_Colliders;

};
