#include "ObjectManager.h"

std::vector<std::shared_ptr<GameObject>> ObjectManager::Objects = *new std::vector<std::shared_ptr<GameObject>>();

void ObjectManager::AddGameObject(GameObject &obj)
{
	std::shared_ptr<GameObject>* ref = new std::shared_ptr<GameObject>(&obj);
	ObjectManager::Objects.push_back(*ref);
}

void ObjectManager::RemoveGameObject(GameObject &obj)
{
	for (unsigned int i = 0; i < ObjectManager::Objects.size(); i++)
	{
		if (ObjectManager::Objects[i].get() != &obj) continue;
		ObjectManager::Objects.erase(ObjectManager::Objects.begin() + i);
		break;
	}
}

void ObjectManager::Update(sf::RenderWindow &window)
{
	for (unsigned int i = 0; i < ObjectManager::Objects.size(); i++)
	{
		IComponent* component = ObjectManager::Objects[i]->GetComponent(EComponentType::Drawing).get();
		IDrawing* drawing = dynamic_cast<IDrawing*>(component);
		// drawing->Update();
		drawing->Draw(window);
	}
}