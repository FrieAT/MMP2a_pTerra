/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "GameObject.h"
#include "IComponent.h"
#include "IPosition.h"
#include "Quadrant.h"
#include "ClassRegistry.h"

// GameObject constructor
GameObject::GameObject(std::string strID)
{
	this->m_strID = strID;
    this->m_bTemporaryCreated = false;
    this->m_bAssistedCreated = false;
}

GameObject::~GameObject()
{
	// Remove all components from game object
    if(m_Components.size() > 0 && m_Components.size() <= (int)EComponentType::MaxItem)
    {
        auto component_it = m_Components.begin();
        while(component_it != m_Components.end())
        {
            delete(component_it->second);
            component_it++;
        }
        m_Components.clear();
    }
}

std::string GameObject::GetID()
{
	return this->m_strID;
}

void GameObject::SetComponent(IComponent* pComponent)
{
	EComponentType eComponentType = pComponent->GetComponentType();
	if (m_Components.size() > 0 && m_Components.find(eComponentType) != m_Components.end())
	{
		delete m_Components[eComponentType];
		m_Components.erase(eComponentType);
	}
    m_Components[eComponentType] = pComponent;
	pComponent->SetAssignedGameObject(this);
    pComponent->Init();
}

void GameObject::RemoveComponent(EComponentType eComponentType)
{
    auto i = m_Components.find(eComponentType);
	if (i != m_Components.end())
	{
        delete i->second;
		m_Components.erase(i);
	}
}

IComponent* GameObject::GetComponent(EComponentType eComponentType)
{
    auto it = m_Components.find(eComponentType);
    if(it == m_Components.end())
    {
        return nullptr;
    }
	return it->second;
}

bool GameObject::IsInFreezedState()
{
    IPosition* pPositionComponent = static_cast<IPosition*>(this->GetComponent(EComponentType::Position));
    // If component has a IPosition (which is maybe always)
    if(pPositionComponent != nullptr)
    {
        // Check if current Quadrant is freezed or not.
        // if so, don´t perform OnFrameUpdate on Observer.
        Quadrant* pQuadrant = pPositionComponent->GetQuadrant();
        if(pQuadrant != nullptr && pQuadrant->GetFreezedState())
        {
            // Skip observer call for this GameObject.
            return true;
        }
    }
    return false;
}

int GameObject::GetAmountOfUsedComponentTypes()
{
    return m_Components.size();
}

SerializeNode* GameObject::Serialize()
{
    SerializeNode* pNode = new SerializeNode("GameObject", ESerializeNodeType::Class, m_strID);
    auto it_components = m_Components.begin();
    while(it_components != m_Components.end())
    {
        SerializeNode* pNodeComponent = new SerializeNode(it_components->second->GetComponentName(), ESerializeNodeType::Class);
        it_components->second->Serialize(pNodeComponent);
        pNode->AddElement(pNodeComponent);
        it_components++;
    }
    return pNode;
}

GameObject* GameObject::Deserialize(SerializeNode *pNode)
{
    GameObject* pGameObject = new GameObject(pNode->GetValue());
    
    unsigned int iCount = 0;
    SerializeNode* pComponentNode = pNode->GetNode(iCount++);
    while(pComponentNode != nullptr)
    {
        IComponent* pComponent = ClassRegistry::GetInstance().CreateComponent(pComponentNode->GetName(), pComponentNode);
        pGameObject->SetComponent(pComponent);
        pComponentNode = pNode->GetNode(iCount++);
    }
    
    return pGameObject;
}