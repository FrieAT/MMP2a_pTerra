/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.h"

struct CollisionEvent {
	GameObject* Body1;
	GameObject* Body2;
	sf::Vector2f normal;
};

class ICollision : public IComponent
{
public:
    ICollision()
    : m_bPhysicsApplyable(true) { }
	virtual ~ICollision() { }
	virtual bool colliding(ICollision* pCollisionBody) = 0;
    bool m_bPhysicsApplyable;
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
        pParentNode->AddElement(new SerializeNode("PhysicsApplyable", ESerializeNodeType::Property, std::to_string(m_bPhysicsApplyable)));
    }
	EComponentType GetComponentType()
	{
		return EComponentType::Collision;
	}
    virtual std::string GetComponentName() { return std::string("ICollision"); }
};