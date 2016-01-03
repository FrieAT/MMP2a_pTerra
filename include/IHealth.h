/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IHealth : public IComponent
{
public:
    IHealth() { }
    IHealth(SerializeNode* pNode)
    : IComponent(pNode)
    {
        m_fHealth = stof((pNode->GetNode("Health"))->GetValue());
    }
	EComponentType GetComponentType()
	{
		return EComponentType::Health;
	}
	float m_fHealth;
	virtual void Damage(float fDamage) = 0;
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
        pParentNode->AddElement(new SerializeNode("Health", ESerializeNodeType::Property, std::to_string(m_fHealth)));
    }
    virtual std::string GetComponentName() { return std::string("IHealth"); }
};