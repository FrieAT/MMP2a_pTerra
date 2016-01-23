/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "CollisionManager.h"
#include "IMovement.h"
#include "ICollision.h"
#include "ObjectManager.h"

void CollisionManager::Update(sf::Time DeltaTime)
{
	if (m_Colliders.size() > 0)
	{
        std::vector<GameObject*> CurrentGameObjects = ObjectManager::GetInstance().GetActiveGameObjects();
		for (unsigned int ship = 0; ship < CurrentGameObjects.size(); ship++)
		{
			if (CurrentGameObjects[ship] == nullptr)
			{
				continue;
			}

            // Check if Observer is a IComponent and check from GameObject within, if it is in a Freezed-State.
            if(CurrentGameObjects[ship]->IsInFreezedState())
            {
                continue;
            }
            
            ICollision* pCollisionComponent = static_cast<ICollision*>(CurrentGameObjects[ship]->GetComponent(EComponentType::Collision));
			if(pCollisionComponent != nullptr)
            {
                // Check if GameObject is a Observer from CollisionManager
                if(!m_Colliders[pCollisionComponent])
                {
                    continue;
                }
                
                for (unsigned int i = 0; i < CurrentGameObjects.size(); i++)
                {
					if (CurrentGameObjects[i] == nullptr)
					{
						continue;
					}

					ICollision* pCollisionComponentOther = static_cast<ICollision*>(CurrentGameObjects[i]->GetComponent(EComponentType::Collision));
                    if(pCollisionComponentOther != nullptr)
                    {
                        //don't check the object with it self
                        if (pCollisionComponentOther == pCollisionComponent)
                        {
                            continue;
                        }
                        
                        // Check if other GameObject is a observer from CollisionManager
                        if(!m_Colliders[pCollisionComponentOther])
                        {
                            continue;
                        }
                        
                        // Check if Observer is a IComponent and check from GameObject within, if it is in a Freezed-State.
                        if(CurrentGameObjects[i]->IsInFreezedState())
                        {
                            continue;
                        }
                        
                        pCollisionComponent->colliding(pCollisionComponentOther);
                    }
                }
            }
		}
	}
	HandleCollisions();
}

void CollisionManager::HandleCollisions()
{
	while (!m_CollisonEvents.empty())
	{
		CollisionEvent col_ev = m_CollisonEvents.top();
		
        // Check if game object is registered with as a collision object.
        if(!m_ActiveGameObjects[col_ev.Body1] || !m_ActiveGameObjects[col_ev.Body2])
        {
            m_CollisonEvents.pop();
            continue;
        }
        
        // Get Collision Models
        ICollision* pCollisionComponentA = static_cast<ICollision*>(col_ev.Body1->GetComponent(EComponentType::Collision));
        ICollision* pCollisionComponentB = static_cast<ICollision*>(col_ev.Body2->GetComponent(EComponentType::Collision));
        
        // Check if Physics are applyable.
        bool PhysicsApplyable = true;
        if(pCollisionComponentA != nullptr && !pCollisionComponentA->m_bPhysicsApplyable)
        {
            PhysicsApplyable = false;
        }
        if(pCollisionComponentB != nullptr && !pCollisionComponentB->m_bPhysicsApplyable)
        {
            PhysicsApplyable = false;
        }
        
		IMovement* body1= static_cast<IMovement*>(col_ev.Body1->GetComponent(EComponentType::Movement));
		IMovement* body2 = static_cast<IMovement*>(col_ev.Body2->GetComponent(EComponentType::Movement));

		// Calculate relative velocity
		sf::Vector2f rv;
        if(body1 != nullptr)
        {
            rv += body1->GetVelocity();
        }
        if(body2 != nullptr)
        {
            rv -= body2->GetVelocity();
        }

		// Calculate relative velocity in terms of the normal direction (length through vector projection)
		float fVelAlongNormal = rv.x * col_ev.normal.x + rv.y * col_ev.normal.y;

		// Do not resolve if velocities are separating
		if (fVelAlongNormal > 0)
        {
			return;
        }
		
		sf::Vector2f Impulse = fVelAlongNormal * col_ev.normal*100.f;
        if(body1 != nullptr && PhysicsApplyable)
        {
            // Apply impulse
            body1->AddForce(body1->GetVelocity() - 0.5f * Impulse);
        }
        if(body2 != nullptr && PhysicsApplyable)
        {
            // Apply impulse
            body2->AddForce(body2->GetVelocity() + 0.5f * Impulse);
        }
		
        // Call EventObservers for Collision.
        if(PhysicsApplyable || (!PhysicsApplyable && !pCollisionComponentA->m_bPhysicsApplyable))
        {
            auto* pCollisionBody1 = &m_CollisionEventObservers[col_ev.Body1];
            for(unsigned int i = 0; i < pCollisionBody1->size(); i++)
            {
                (*pCollisionBody1)[i]->OnCollisionEvent(col_ev.Body2, Impulse);
            }
        }
        
        if(PhysicsApplyable || (!PhysicsApplyable && !pCollisionComponentB->m_bPhysicsApplyable))
        {
            auto* pCollisionBody2 = &m_CollisionEventObservers[col_ev.Body2];
            for(unsigned int i = 0; i < pCollisionBody2->size(); i++)
            {
                (*pCollisionBody2)[i]->OnCollisionEvent(col_ev.Body1, Impulse);
            }
        }
        
        m_CollisonEvents.pop();
    }

}

void CollisionManager::RegisterCollisionbody(ICollision* pCollisionBody)
{
    if(pCollisionBody->GetAssignedGameObject() == nullptr)
    {
        throw std::runtime_error("This component references to a null-pointer game-object. Maybe register in Init()?");
    }
	m_Colliders[pCollisionBody] = true;
    m_ActiveGameObjects[pCollisionBody->GetAssignedGameObject()] = true;
}

void CollisionManager::UnregisterCollisionbody(ICollision* pCollisionBody)
{
    if(pCollisionBody->GetAssignedGameObject() == nullptr)
    {
        throw std::runtime_error("This component references to a null-pointer game-object. Maybe unregister after or in Init()?");
    }
	m_Colliders.erase(pCollisionBody);
    m_ActiveGameObjects.erase(pCollisionBody->GetAssignedGameObject());
}

void CollisionManager::Clear()
{
	m_Colliders.clear();
    m_CollisonEvents = std::stack<CollisionEvent>();
}

void CollisionManager::RegisterCollisionEvent(ICollisionEventObserver* pThisComponent, GameObject* pGameObject)
{
    if(pThisComponent == nullptr || pGameObject == nullptr)
    {
        throw std::runtime_error("Null-pointer reference for pThisComponent or pGameObject.");
    }
    m_CollisionEventObservers[pGameObject].push_back(pThisComponent);
}

void CollisionManager::UnregisterCollisionEvent(ICollisionEventObserver* pThisComponent, GameObject* pGameObject)
{
    if(pThisComponent == nullptr || pGameObject == nullptr)
    {
        throw std::runtime_error("Null-pointer reference for pThisComponent or pGameObject.");
    }
    unsigned int size = m_CollisionEventObservers[pGameObject].size();
    if(size < 1)
    {
        throw std::runtime_error("No components for pGameObject found.");
    }
    for(unsigned int i = 0; i < size; i++)
    {
        if(m_CollisionEventObservers[pGameObject][i] == pThisComponent)
        {
            m_CollisionEventObservers[pGameObject].erase(m_CollisionEventObservers[pGameObject].begin() + i);
            if(size == 1)
            {
                m_CollisionEventObservers.erase(pGameObject);
            }
            break;
        }
    }
}
