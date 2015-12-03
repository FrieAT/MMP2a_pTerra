/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IQuadrantObserver.h"
#include "Quadrant.h"

enum class WorldManagerSettings
{
    ChunkSizeWidth,
    ChunkSizeHeight
};

class WorldManager
{
public:
    const sf::Vector2f m_ChunkSize;
    
    static WorldManager& GetInstance()
    {
        static WorldManager g_Instance(sf::Vector2f(3000.f, 3000.f));
        return g_Instance;
    }
    void AddQuadrant(Quadrant* Quadrant);
    Quadrant* GetQuadrant(std::pair<int,int> QuadrantIndex);
    void Update(sf::RenderWindow* pWindow);
    void RegisterEventObserver(IQuadrantObserver* pObserver);
    void UnregisterEventObserver(IQuadrantObserver* pObserver);
    void Clear();
private:
    WorldManager(sf::Vector2f ChunkSize);
    WorldManager(const WorldManager&) = delete;
    void operator= (const WorldManager&) = delete;
    std::vector<IQuadrantObserver*> m_Observers;
    std::map<std::pair<int, int>, Quadrant*> m_Quadrants;
    void UpdateEventObserver(std::string strEvent);
};
