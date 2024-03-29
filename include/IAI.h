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
	virtual std::string GetComponentName() { return std::string("IAI"); }

	virtual void Serialize(SerializeNode* pParentNode)
	{
		IComponent::Serialize(pParentNode);
		//this->IComponent::Serialize(pParentNode);
		//pParentNode->AddElement(new SerializeNode("Has_AI", ESerializeNodeType::Property, std::to_string(m_bPhysicsApplyable)));
	}

	static void Deserialize(SerializeNode* pNode, IAI* pParentComponent)
	{

	}

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
		return EComponentType::AI;
	}
};