/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "CollisionManager.h"
#include "IMovement.h"

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

void CollisionManager::HandleCollisions()
{
	while (m_CollisonEvents.size()>0)
	{
		CollisionEvent col_ev = m_CollisonEvents.top();
		
		IMovement* body1= static_cast<IMovement*>(col_ev.Body1.GetComponent(EComponentType::Movement));
		body1->GetMovementVector();
		IMovement* body2 = static_cast<IMovement*>(col_ev.Body2.GetComponent(EComponentType::Movement));
		body2->GetMovementVector();
		
		m_CollisonEvents.pop();
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

