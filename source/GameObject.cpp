/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "GameObject.h"
#include "IComponent.h"

// GameObject constructor
GameObject::GameObject(std::string strID)
{
	this->m_strID = strID;
}

GameObject::~GameObject()
{
	// Remove all components from game object
    for(int i = 0; i < (int)EComponentType::MaxItem; i++)
    {
        RemoveComponent((EComponentType)i);
    }
}

std::string GameObject::GetID()
{
	return this->m_strID;
}

void GameObject::SetComponent(IComponent* pComponent)
{
	EComponentType eComponentType = pComponent->GetComponentType();
	if (m_Components[eComponentType] != nullptr)
	{
		delete m_Components[eComponentType];
		m_Components.erase(eComponentType);
	}
    m_Components[eComponentType] = pComponent;
	pComponent->SetAssignedGameObject(this);
    pComponent->Init();
}

void GameObject::RemoveComponent(const EComponentType& eComponentType)
{
    auto i = m_Components.find(eComponentType);
	if (i != m_Components.end())
	{
        delete i->second;
		m_Components.erase(i);
	}
}

IComponent* GameObject::GetComponent(const EComponentType& eComponentType)
{
	return m_Components[eComponentType];
}