/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IHealth : public IComponent
{
public:
    IHealth() { }
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
    static IComponent* Deserialize(SerializeNode* pNode, IHealth* pParentComponent)
    {
        float fHealth = stof((pNode->GetNode("Health"))->GetValue());
        
        pParentComponent->m_fHealth = fHealth;
    }
    virtual std::string GetComponentName() { return std::string("IHealth"); }
};