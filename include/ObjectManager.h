#pragma once

#include <vector>

#include "IDrawing.h"

#include "GameObject.h"

class ObjectManager
{
public:
	static ObjectManager& GetInstance()
	{
		static ObjectManager instance;
		return instance;
	}
	void AddGameObject(GameObject* obj);
	void RemoveGameObject(GameObject* obj);
    void RemoveAllGameObjects();
	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void Clear();
private:
	ObjectManager();
	ObjectManager(ObjectManager const&) = delete;
	void operator= (ObjectManager const&) = delete;
	std::map<std::string, std::vector<GameObject*>> objects;
	std::vector<std::string> drawOrder;
};
