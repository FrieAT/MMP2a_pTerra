/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "CollisionManager.h"
#include "IMovement.h"
#include "ICollision.h"

void CollisionManager::Update(sf::Time DeltaTime)
{
	if (m_Colliders.size() > 0)
	{
		for (int ship = 0; ship < m_Colliders.size(); ship++)
		{
			ICollision* current_col = m_Colliders[ship];
			for (int i = 0; i < m_Colliders.size(); i++)
			{
				if (m_Colliders[i] == current_col) continue;	//don't check the object with it self
				current_col->colliding(m_Colliders[i]);
				
			}
		}
	}
	HandleCollisions();
}

void CollisionManager::HandleCollisions()
{
	while (m_CollisonEvents.size()>0)
	{
		CollisionEvent col_ev = m_CollisonEvents.top();
		
		IMovement* body1= static_cast<IMovement*>(col_ev.Body1->GetComponent(EComponentType::Movement));
		IMovement* body2 = static_cast<IMovement*>(col_ev.Body2->GetComponent(EComponentType::Movement));
		
		
		std::cout << "blub" << std::endl;


		// Calculate relative velocity
		sf::Vector2f rv = body1->GetVelocity() - body2->GetVelocity();

		// Calculate relative velocity in terms of the normal direction (length through vector projection)
		float velAlongNormal = rv.x * col_ev.normal.x + rv.y * col_ev.normal.y;

		// Do not resolve if velocities are separating
		if (velAlongNormal > 0)
			return;

		// Apply impulse
		sf::Vector2f impulse = velAlongNormal * col_ev.normal;

		body1->AddForce(body1->GetVelocity() - 0.5f * impulse);
		body2->AddForce(body2->GetVelocity() + 0.5f * impulse);
		

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

