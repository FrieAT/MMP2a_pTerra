/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "EComponentType.h"
#include "GameObject.h"

class IComponent
{
public:
    IComponent() : m_pGameObject(nullptr) { }
    virtual ~IComponent() { }
	virtual EComponentType GetComponentType() = 0;
	void SetAssignedGameObject(GameObject* pObject)
	{
        m_pGameObject = pObject;
	}
	GameObject* GetAssignedGameObject()
	{
		return m_pGameObject;
	}
private:
    GameObject* m_pGameObject;
};
