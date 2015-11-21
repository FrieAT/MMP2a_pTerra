#pragma once

#include <vector>

#include "IDrawing.h"

#include "GameObject.h"

class ObjectManager
{
public:
	ObjectManager() = delete;
	static void AddGameObject(GameObject* obj);
	static void RemoveGameObject(GameObject* obj);
    static void RemoveAllGameObjects();
	static void Update(sf::Time deltaTime);
	static void Draw(sf::RenderWindow* window);
private:
	static std::map<std::string, std::vector<GameObject*>> objects;
	static std::vector<std::string> drawOrder;
};
