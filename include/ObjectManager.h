/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

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
	void RemoveGameObject(GameObject* pObject, bool bDelete = true);
    void RemoveAllGameObjects();
    void AddQuadrant(Quadrant* pChunk);
    void RemoveQuadrant(Quadrant* pChunk);
    void RemoveAllQuadrants();
    const std::vector<GameObject*>& GetActiveGameObjects();
	const std::unordered_map<std::pair<std::string, Quadrant*>, std::vector<GameObject*>, pairhash>& GetAllGameObjects() { return m_Objects; }
	void Update(sf::Time DeltaTime);
	void Draw(sf::RenderWindow* pWindow);
	void Clear();
private:
	ObjectManager();
	ObjectManager(const ObjectManager&) = delete;
	void operator= (const ObjectManager&) = delete;
    std::unordered_map<std::pair<std::string, Quadrant*>, std::vector<GameObject*>, pairhash> m_Objects;
	std::vector<GameObject*> m_CleanUp;
    std::vector<GameObject*> m_ActiveGameObjects;
	std::vector<std::string> m_DrawOrder;
    std::unordered_map<std::pair<int,int>, Quadrant*, pairhash> m_Quadrants;
    std::pair<std::string, Quadrant*> GetKeyFromGameObject(GameObject* pGameObject);
    void PerformGameObjectCleanUp();
};
