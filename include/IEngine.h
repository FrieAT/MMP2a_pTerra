/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"

class IEngine : public IComponent
{
public:
	virtual float GetFuel() = 0;
	virtual float GetMaxFuel() = 0;
	virtual void AddFuel(float fAddFuel) = 0;

	EComponentType GetComponentType()
	{
		return EComponentType::Engine;
	}
	virtual void Serialize(SerializeNode* pParentNode)
	{
		this->IComponent::Serialize(pParentNode);
	}
	static void Deserialize(SerializeNode* pNode, IEngine* pParentComponent)
	{
		// Nothing to extract here...
	}
	virtual std::string GetComponentName() { return std::string("IEngine"); }
};