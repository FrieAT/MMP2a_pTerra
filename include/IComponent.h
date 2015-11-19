#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "EComponentType.h"

class GameObject;

class IComponent
{
public:
	virtual EComponentType GetComponentType() = 0;
	void SetAssignedGameObject(GameObject* obj)
	{
		GameObj = obj;
	}
	GameObject* GetAssignedGameObject()
	{
		return GameObj;
	}
private:
	GameObject* GameObj;
};
