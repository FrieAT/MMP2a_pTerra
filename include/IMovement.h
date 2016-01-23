/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IMovement : public IComponent
{
public:
    IMovement() { }
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
        unsigned int count = 0;
        while(it != impulses.end())
        {
            SerializeNode* pNodeImpulse = new SerializeNode(std::to_string(count), ESerializeNodeType::List);
            pNodeImpulse->AddElement(new SerializeNode("X", ESerializeNodeType::Property, std::to_string((*it).x)));
            pNodeImpulse->AddElement(new SerializeNode("Y", ESerializeNodeType::Property, std::to_string((*it).y)));
            pNodeImpulses->AddElement(pNodeImpulse);
            it++;
            count++;
        }
        pParentNode->AddElement(pNodeImpulses);
        
        pParentNode->AddElement(new SerializeNode("AccelerationX", ESerializeNodeType::Property, std::to_string(acceleration.x)));
        pParentNode->AddElement(new SerializeNode("AccelerationY", ESerializeNodeType::Property, std::to_string(acceleration.y)));
        pParentNode->AddElement(new SerializeNode("VelocityX", ESerializeNodeType::Property, std::to_string(velocity.x)));
        pParentNode->AddElement(new SerializeNode("VelocityY", ESerializeNodeType::Property, std::to_string(velocity.y)));
        pParentNode->AddElement(new SerializeNode("Mass", ESerializeNodeType::Property, std::to_string(mass)));
        pParentNode->AddElement(new SerializeNode("InvMass", ESerializeNodeType::Property, std::to_string(invMass)));
    }
    static void Deserialize(SerializeNode* pNode, IMovement* pParentComponent)
    {
        SerializeNode* pNodeImpulses = pNode->GetNode("Impulses");
        unsigned int count = 0;
        float x, y;
        do
        {
            SerializeNode* pCurrentNode = pNodeImpulses->GetNode(std::to_string(count++));
            if(pCurrentNode == nullptr)
            {
                pNodeImpulses = nullptr;
                continue;
            }
            x = stof((pCurrentNode->GetNode("X"))->GetValue());
            y = stof((pCurrentNode->GetNode("Y"))->GetValue());
            
            pParentComponent->impulses.push_back(sf::Vector2f(x, y));
        } while(pNodeImpulses != nullptr);
        
        x = stof((pNode->GetNode("AccelerationX"))->GetValue());
        y = stof((pNode->GetNode("AccelerationY"))->GetValue());
        pParentComponent->acceleration = sf::Vector2f(x, y);
        
        x = stof((pNode->GetNode("VelocityX"))->GetValue());
        y = stof((pNode->GetNode("VelocityY"))->GetValue());
        pParentComponent->velocity = sf::Vector2f(x, y);
        
        pParentComponent->mass = stof((pNode->GetNode("Mass"))->GetValue());
        
        pParentComponent->invMass = stof((pNode->GetNode("InvMass"))->GetValue());
        
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
