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

	void SetComponent(std::shared_ptr<IComponent> component);
	void RemoveComponent(EComponentType component_type);
	std::shared_ptr<IComponent> GetComponent(EComponentType component_type);

private:
	std::map<EComponentType, std::shared_ptr<IComponent>> Components;
};
