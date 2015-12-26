/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "EComponentType.h"

class IComponent;

class GameObject
{
public:
	GameObject(std::string strID);
	~GameObject();

	std::string GetID();
	void SetComponent(IComponent* pComponent);
	void RemoveComponent(const EComponentType& eComponentType);
	IComponent* GetComponent(const EComponentType& eComponentType);
    bool IsInFreezedState();
private:
	std::string m_strID;
	std::map<EComponentType, IComponent*> m_Components;
};
