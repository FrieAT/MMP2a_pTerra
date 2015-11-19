#pragma once

#include <vector>

#include "IDrawing.h"

#include "GameObject.h"

class ObjectManager
{
public:
	static void AddGameObject(GameObject* obj);
	static void RemoveGameObject(GameObject* obj);
    static void RemoveAllGameObjects();
	static void Update(sf::RenderWindow* window);
private:
	static std::vector<std::shared_ptr<GameObject>> Objects;
};
