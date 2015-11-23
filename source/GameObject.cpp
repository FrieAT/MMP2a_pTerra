#include "GameObject.h"

#include "IComponent.h"

// GameObject constructor
GameObject::GameObject(std::string id)
{
	this->id = id;
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
	return this->id;
}

void GameObject::SetComponent(IComponent* component)
{
	EComponentType component_type = component->GetComponentType();
	if (Components[component_type] != nullptr)
	{
		Components.erase(component_type);
	}
    Components[component_type] = component;
	component->SetAssignedGameObject(this);
}

void GameObject::RemoveComponent(const EComponentType &component_type)
{
    auto it = Components.find(component_type);
	if (it != Components.end())
	{
        delete it->second;
		Components.erase(it);
	}
}

IComponent* GameObject::GetComponent(const EComponentType &component_type)
{
	return Components[component_type];
}