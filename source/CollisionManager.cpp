/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "CollisionManager.h"

void CollisionManager::Update(sf::Time DeltaTime)
{
	if (m_Colliders.size() > 0)
	{
		for (int ship = 0; ship < m_Colliders.size(); ship++)
		{
			ICollision* current_col = m_Colliders[ship];
			for (int i = 0; i < m_Colliders.size(); i++)
			{
				if (m_Colliders[i] == current_col) continue;
				current_col->colliding(m_Colliders[i]);
			}
		}
	}
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

void CollisionManager::Clear()
{
	m_Colliders.clear();
	m_Colliders.shrink_to_fit();
}

