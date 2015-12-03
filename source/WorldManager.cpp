/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "WorldManager.h"
#include "ObjectManager.h"
#include "GameObjectFactory.h"

void WorldManager::AddQuadrant(Quadrant *Quadrant)
{
    if(Quadrant == nullptr)
    {
        throw std::runtime_error(std::string("A null-reference exception happend by Adding a Quadrant (AddQuadrant)"));
    }
    long lIndex = Quadrant->GetIndex();
    if (m_Quadrants[lIndex] != nullptr)
    {
        return;
    }
    m_Quadrants[lIndex] = Quadrant;

    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    sf::Vector2f TopLeftPosition = Quadrant->GetTopLeftPosition();
    const int MaxRandItems = 1 + rand() % 8;
    for(int i = 0; i < MaxRandItems; i++)
    {
        float x = TopLeftPosition.x + rand() % static_cast<int>(ChunkSize.x);
        float y = TopLeftPosition.y + rand() % static_cast<int>(ChunkSize.y);
        
        GameObject* asteroid = GameObjectFactory::CreateAsteroid(sf::Vector2f(x, y), rand() % 360, 50 + rand() % 150);
        ObjectManager::GetInstance().AddGameObject(asteroid);
    }
}

void WorldManager::Update(sf::RenderWindow *pWindow)
{
    // DEBUG Purpose: Zeige die Quadranten.
    for(int i = 0; i < m_Quadrants.size(); i++)
    {
        if(m_Quadrants[i] == nullptr) continue;
        sf::RectangleShape shape;
        sf::Color color(255.f, 128.f, 0.f, 128.f);
        shape.setSize(WorldManager::GetInstance().m_ChunkSize);
        shape.setPosition(m_Quadrants[i]->GetTopLeftPosition());
        shape.setFillColor(color);
        pWindow->draw(shape);
    }
}

void WorldManager::RegisterEventObserver(IQuadrantObserver* pObserver)
{
    m_Observers.push_back(pObserver);
}

void WorldManager::UnregisterEventObserver(IQuadrantObserver* pObserver)
{
    for(unsigned int i = 0; i < m_Observers.size(); i++)
    {
        if(m_Observers[i] != pObserver) continue;
        m_Observers.erase(m_Observers.begin() + i);
        break;
    }
}

void WorldManager::Clear()
{
    m_Observers.clear();
    m_Observers.shrink_to_fit();
}