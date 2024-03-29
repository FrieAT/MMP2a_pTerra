/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"
#include "Quadrant.h"

class IPosition : public IComponent
{
public:
	IPosition(sf::Vector2f Position, sf::Vector2f Origin)
	{
		this->m_Position = Position;
		this->m_fRotation = 0.0;
		this->m_Origin = Origin;
	}
    virtual ~IPosition() { }
	virtual void SetPosition(sf::Vector2f Position) = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual sf::Vector2f GetCenter() = 0;
	virtual float GetRotation() = 0;
	virtual void SetRotation(float rotation) = 0;
	virtual void SetOrigin(sf::Vector2f Origin) = 0;
	virtual sf::Vector2f GetOrigin() = 0;
    virtual Quadrant* GetQuadrant() { return nullptr; }
    
	EComponentType GetComponentType()
	{
		return EComponentType::Position;
	}
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
        pParentNode->AddElement(new SerializeNode("PositionX", ESerializeNodeType::Property, std::to_string(m_Position.x)));
        pParentNode->AddElement(new SerializeNode("PositionY", ESerializeNodeType::Property, std::to_string(m_Position.y)));
        pParentNode->AddElement(new SerializeNode("OriginX", ESerializeNodeType::Property, std::to_string(m_Origin.x)));
        pParentNode->AddElement(new SerializeNode("OriginY", ESerializeNodeType::Property, std::to_string(m_Origin.y)));
        pParentNode->AddElement(new SerializeNode("Rotation", ESerializeNodeType::Property, std::to_string(m_fRotation)));
    }
    static void Deserialize(SerializeNode* pNode, IPosition* pParentComponent)
    {
        float x, y;
        
        x = stof((pNode->GetNode("PositionX"))->GetValue());
        y = stof((pNode->GetNode("PositionY"))->GetValue());
        pParentComponent->m_Position = sf::Vector2f(x, y);
        
        x = stof((pNode->GetNode("OriginX"))->GetValue());
        y = stof((pNode->GetNode("OriginY"))->GetValue());
        pParentComponent->m_Origin = sf::Vector2f(x, y);
        
        pParentComponent->m_fRotation = stof((pNode->GetNode("Rotation"))->GetValue());
    }
    virtual std::string GetComponentName() { return std::string("IPosition"); }
protected:
	sf::Vector2f m_Position;
	sf::Vector2f m_Origin;
	float m_fRotation;
};