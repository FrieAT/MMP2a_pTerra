/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <vector>

#include "IDrawing.h"
#include "GameObject.h"
#include "Quadrant.h"

class ObjectManager
{
public:
	static ObjectManager& GetInstance()
	{
		static ObjectManager g_Instance;
		return g_Instance;
	}
	void AddGameObject(GameObject* pObject);
	void RemoveGameObject(GameObject* pObject);
    void RemoveAllGameObjects();
    void AddQuadrant(Quadrant* pChunk);
    void RemoveQuadrant(Quadrant* pChunk);
    void RemoveAllQuadrants();
	void Update(sf::Time DeltaTime);
	void Draw(sf::RenderWindow* pWindow);
	void Clear();
private:
	ObjectManager();
	ObjectManager(const ObjectManager&) = delete;
	void operator= (const ObjectManager&) = delete;
    std::map<std::pair<std::string, Quadrant*>, std::vector<GameObject*>> m_Objects;
	std::vector<GameObject*> m_CleanUp;
	std::vector<std::string> m_DrawOrder;
    std::map<std::pair<int,int>, Quadrant*> m_Quadrants;
    std::pair<std::string, Quadrant*> GetKeyFromGameObject(GameObject* pGameObject);
    std::pair<std::string, Quadrant*> GetKeyFromIDAndQuadrant(std::string object_id, Quadrant* pQuadrant);
    void PerformGameObjectCleanUp();
};
