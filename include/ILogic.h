/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IComponent.h"
#include "ELogicType.h"

class ILogic : public IComponent
{
public:
	virtual void Action(GameObject* pPossibleOther = nullptr) = 0;
	virtual ELogicType GetLogicType() = 0;
	EComponentType GetComponentType()
	{
		return EComponentType::Logic;
	}
	virtual void Serialize(SerializeNode* pParentNode)
	{
		this->IComponent::Serialize(pParentNode);
	}
	static void Deserialize(SerializeNode* pNode, ILogic* pParentComponent)
	{

	}
	virtual std::string GetComponentName() { return std::string("ILogic"); }
private:

};