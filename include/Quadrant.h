/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "EQuadrantPos.h"

class Quadrant
{
public:
    Quadrant(sf::Vector2f TopLeftPosition);
    sf::Vector2f GetTopLeftPosition();
    bool GetFreezedState();
    std::pair<int,int> GetIndex();
    unsigned RegisterGameObject(GameObject* pObject); // TODO: Not used, but should be.
    void UnregisterGameObject(int iIndex); // TODO: Not used, but should be.
    Quadrant* GetNeighbour(EQuadrantPos eChunkPosition, char uChunkDepth = 2);
private:
    std::pair<int,int> m_Index;
    sf::Vector2f m_TopLeftPosition;
    bool m_bFreezed;
    std::vector<GameObject*> m_GameObjects;
    
    sf::Vector2f CalculatePositionForNeighbour(EQuadrantPos eChunkPosition);
    std::pair<int,int> GetQuadrantIndexAtPos(sf::Vector2f TopLeftPosition);
    sf::Vector2f GetQuadrantCorrectedPos(sf::Vector2f Position);
};