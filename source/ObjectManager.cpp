#include "ObjectManager.h"

std::map<std::string, std::vector<GameObject*>> ObjectManager::objects;
std::vector<std::string> ObjectManager::drawOrder{ "background", "asteroid", "missile", "ship", "text" }; // change draw order here! first entry = first to draw

void ObjectManager::AddGameObject(GameObject* obj)
{
	objects[obj->GetID()].push_back(obj);
}

void ObjectManager::RemoveGameObject(GameObject* obj)
{
	std::string id = obj->GetID();
    auto it = objects[id].begin();
    while(it != objects[id].end())
	{
        if(*it != obj) continue;
		objects[id].erase(it);
		break;
	}
}

void ObjectManager::RemoveAllGameObjects()
{
	for (unsigned int s = 0; s < ObjectManager::drawOrder.size(); s++)
	{
		std::string* draw_order_type = &ObjectManager::drawOrder[s];
		for (unsigned int i = 0; i < ObjectManager::objects[*draw_order_type].size(); i++)
		{
			delete ObjectManager::objects[*draw_order_type][i];
			ObjectManager::objects[*draw_order_type].erase(objects[*draw_order_type].begin() + i);
		}
	}
	/*for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects.erase(objects.begin() + i);
	}*/
}

void ObjectManager::Update(sf::Time deltaTime)
{
	// Update function for each object?
	// Things like health, shield regenaration, ...
}

void ObjectManager::Draw(sf::RenderWindow* window)
{
	for (unsigned int s = 0; s < ObjectManager::drawOrder.size(); s++)
	{
		std::string* draw_order_type = &ObjectManager::drawOrder[s];
		for (unsigned int i = 0; i < ObjectManager::objects[*draw_order_type].size(); i++)
		{
			IDrawing* drawing = ((IDrawing*)objects[*draw_order_type][i]->GetComponent(EComponentType::Drawing));
            if(drawing == nullptr) continue;
			drawing->Draw(window);
		}
	}
}