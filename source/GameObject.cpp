#include "GameObject.h"

#include "IComponent.h"

// GameObject constructor
GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	// Remove all components from game object
	for (int i = 1; i != (int)EComponentType::MaxItem; i++)
	{
		RemoveComponent((EComponentType)i);
	}
}

void GameObject::SetComponent(std::shared_ptr<IComponent> component)
{
	EComponentType component_type = component->GetComponentType();
	if (Components[component_type] != nullptr)
	{
		Components.erase(component_type); //< shared_ptr calles automatically destructor
	}
	Components[component_type] = component;
	component->SetAssignedGameObject(*this);
}

void GameObject::RemoveComponent(EComponentType component_type)
{
	if (Components[component_type] != nullptr)
	{
		Components.erase(component_type); //< shared_ptr calles automatically destructor
	}
}

std::shared_ptr<IComponent> GameObject::GetComponent(EComponentType component_type)
{
	return Components[component_type];
}