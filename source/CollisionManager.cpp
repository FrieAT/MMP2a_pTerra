/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "CollisionManager.h"

void CollisionManager::Update(sf::Time DeltaTime)
{

}

void CollisionManager::RegisterCollisionbody(ICollision * Collisionbody)
{
	m_Colliders.push_back(Collisionbody);
}

void CollisionManager::UnregisterCollisionbody(ICollision * Collisionbody)
{
	for (unsigned int i = 0; i < m_Colliders.size(); i++)
	{
		if (m_Colliders[i] != Collisionbody) continue;
		m_Colliders.erase(m_Colliders.begin() + i);
		break;
	}
}

void CollisionManager::clear()
{
	m_Colliders.clear();
	m_Colliders.shrink_to_fit();
}

