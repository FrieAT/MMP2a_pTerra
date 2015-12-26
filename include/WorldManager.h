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
    const unsigned long m_MaxRandomCoordinates;
    
    static WorldManager& GetInstance()
    {
        static WorldManager g_Instance(sf::Vector2f(10000.f, 10000.f), 10000, 2);
        return g_Instance;
    }
    void AddQuadrant(Quadrant* Quadrant);
    char GetChunkDepth();
    Quadrant* GetQuadrant(std::pair<int,int> QuadrantIndex);
    std::pair<int,int> GetQuadrantIndexAtPos(sf::Vector2f TopLeftPosition);
    sf::Vector2f GetQuadrantCorrectedPos(sf::Vector2f Position);
    sf::Vector2f GetRandomChunkPositionFromChunk(Quadrant* pChunk);
    void Update(sf::RenderWindow* pWindow);
    void RegisterEventObserver(IQuadrantObserver* pObserver);
    void UnregisterEventObserver(IQuadrantObserver* pObserver);
    void Clear();
private:
    WorldManager(sf::Vector2f ChunkSize, unsigned long MaxRandomCoordinates, char iChunkDepth);
    WorldManager(const WorldManager&) = delete;
    void operator= (const WorldManager&) = delete;
    std::vector<IQuadrantObserver*> m_Observers;
    std::map<std::pair<int, int>, Quadrant*> m_Quadrants;
    std::vector<sf::Vector2f> m_RandomCoordinates;
    unsigned long m_IndexRandomCoordinates;
    char m_iChunkDepth;
    void UpdateEventObserver(std::string strEvent);
};
