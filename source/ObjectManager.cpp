#include "ObjectManager.h"

std::vector<GameObject*> ObjectManager::Objects;

void ObjectManager::AddGameObject(GameObject* obj)
{
	Objects.push_back(obj);
}

void ObjectManager::RemoveGameObject(GameObject* obj)
{
    auto it = Objects.begin();
    while(it != Objects.end())
	{
        if(*it != obj) continue;
		Objects.erase(it);
		break;
	}
}

void ObjectManager::RemoveAllGameObjects()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		delete Objects[i];
		Objects.erase(Objects.begin() + i);
	}
}

void ObjectManager::Update(sf::RenderWindow* window)
{
	for (unsigned int i = 0; i < Objects.size(); i++)
	{
		IDrawing* drawing = ((IDrawing*)Objects[i]->GetComponent(EComponentType::Drawing));
		// drawing->Update();
		drawing->Draw(window);
	}
}