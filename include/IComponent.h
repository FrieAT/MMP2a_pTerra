/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "EComponentType.h"
#include "GameObject.h"
#include "SerializeNode.h"

class IComponent
{
public:
    IComponent() : m_pGameObject(nullptr) { }
    virtual ~IComponent() { }
    virtual void Init() { }
	virtual EComponentType GetComponentType() = 0;
    virtual void Serialize(SerializeNode* pParentNode) { }
	void SetAssignedGameObject(GameObject* pObject)
	{
        m_pGameObject = pObject;
	}
	GameObject* GetAssignedGameObject()
	{
		return m_pGameObject;
	}
    virtual std::string GetComponentName() { return std::string("IComponent"); }
private:
    GameObject* m_pGameObject;
};
