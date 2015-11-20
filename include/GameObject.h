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
	GameObject();
	~GameObject();

	void SetComponent(IComponent* component);
	void RemoveComponent(const EComponentType &component_type);
	IComponent* GetComponent(const EComponentType &component_type);
    std::map<EComponentType, IComponent*> Components;
private:
	// std::map<EComponentType, std::shared_ptr<IComponent>> Components;
};
