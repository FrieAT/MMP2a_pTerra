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
        static WorldManager g_Instance;
        return g_Instance;
    }
    void AddQuadrant(Quadrant* Quadrant);
    void Update(sf::RenderWindow* pWindow);
    void RegisterEventObserver(IQuadrantObserver* pObserver);
    void UnregisterEventObserver(IQuadrantObserver* pObserver);
    void Clear();
private:
    WorldManager() : m_ChunkSize(sf::Vector2f(200.f, 200.f)) { }
    WorldManager(const WorldManager&) = delete;
    void operator= (const WorldManager&) = delete;
    std::vector<IQuadrantObserver*> m_Observers;
    std::map<long, Quadrant*> m_Quadrants;
    void UpdateEventObserver(std::string strEvent);
};
