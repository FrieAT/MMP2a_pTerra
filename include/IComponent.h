#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "EComponentType.h"

#include "GameObject.h"

class IComponent
{
public:
    IComponent() : GameObj(nullptr) { }
    virtual ~IComponent() { }
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
