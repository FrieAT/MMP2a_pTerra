#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <exception>

#include "EComponentType.h"

class IComponent;

class GameObject
{
public:
	GameObject(std::string id);
	~GameObject();

	std::string GetID();
	void SetComponent(IComponent* component);
	void RemoveComponent(const EComponentType &component_type);
	IComponent* GetComponent(const EComponentType &component_type);
	std::map<EComponentType, IComponent*> Components; // Make private? Shouldn't be changeable from everyone
	
private:
	std::string id;
	// std::map<EComponentType, std::shared_ptr<IComponent>> Components;
};
