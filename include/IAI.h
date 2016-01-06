/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IAI : public IComponent
{
public:
	IAI() { }
	virtual ~IAI() { }
	virtual std::string GetComponentName() { return std::string("IKI"); }

	virtual void Serialize(SerializeNode* pParentNode)
	{
		//this->IComponent::Serialize(pParentNode);
		//pParentNode->AddElement(new SerializeNode("Has_KI", ESerializeNodeType::Property, std::to_string(m_bPhysicsApplyable)));
	}

	virtual void Deserialize(SerializeNode* pNode, IAI* pParentComponent) { }

	//virtual void Serialize(SerializeNode* pParentNode)
	//{
	//	this->IComponent::Serialize(pParentNode);
	//	pParentNode->AddElement(new SerializeNode("Health", ESerializeNodeType::Property, std::to_string(m_fHealth)));
	//}
	//static void Deserialize(SerializeNode* pNode, IHealth* pParentComponent)
	//{
	//	float fHealth = stof((pNode->GetNode("Health"))->GetValue());

	//	pParentComponent->m_fHealth = fHealth;
	//}

	EComponentType GetComponentType()
	{
		return EComponentType::KI;
	}
};