/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "EComponentType.h"
#include "SerializeNode.h"

class IComponent;

class GameObject
{
public:
	GameObject(std::string strID);
	~GameObject();

	std::string GetID();
	void SetComponent(IComponent* pComponent);
	void RemoveComponent(EComponentType eComponentType);
	IComponent* GetComponent(EComponentType eComponentType);
    int GetAmountOfUsedComponentTypes();
    bool IsInFreezedState();
    SerializeNode* Serialize();
    
private:
	std::string m_strID;
	std::map<EComponentType, IComponent*> m_Components;
};
