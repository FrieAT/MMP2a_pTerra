/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"
#include <list>

class IMovement : public IComponent
{
public:
    virtual ~IMovement() { }
    
	virtual sf::Vector2f GetVelocity() { return velocity; };
	virtual void AddForce(sf::Vector2f force) { impulses.push_back(force); };

	EComponentType GetComponentType()
	{
		return EComponentType::Movement;
	}
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
        
        SerializeNode* pNodeImpulses = new SerializeNode("Impulses", ESerializeNodeType::List);
        auto it = impulses.begin();
        while(it != impulses.end())
        {
            SerializeNode* pNodeImpulse = new SerializeNode("Impulse", ESerializeNodeType::List);
            pNodeImpulse->AddElement(new SerializeNode("X", ESerializeNodeType::Property, std::to_string((*it).x)));
            pNodeImpulse->AddElement(new SerializeNode("Y", ESerializeNodeType::Property, std::to_string((*it).y)));
            pNodeImpulses->AddElement(pNodeImpulse);
            it++;
        }
        pParentNode->AddElement(pNodeImpulses);
        
        pParentNode->AddElement(new SerializeNode("AccelerationX", ESerializeNodeType::Property, std::to_string(acceleration.x)));
        pParentNode->AddElement(new SerializeNode("AccelerationY", ESerializeNodeType::Property, std::to_string(acceleration.y)));
        pParentNode->AddElement(new SerializeNode("VelocityX", ESerializeNodeType::Property, std::to_string(velocity.x)));
        pParentNode->AddElement(new SerializeNode("VelocityY", ESerializeNodeType::Property, std::to_string(velocity.y)));
        pParentNode->AddElement(new SerializeNode("Mass", ESerializeNodeType::Property, std::to_string(mass)));
        pParentNode->AddElement(new SerializeNode("InvMass", ESerializeNodeType::Property, std::to_string(invMass)));
    }
    virtual std::string GetComponentName() { return std::string("IMovement"); }
protected:
	sf::Clock m_DeltaClock;
	std::list<sf::Vector2f> impulses;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	float mass;
	float invMass;

};
