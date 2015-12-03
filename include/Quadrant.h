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
    unsigned RegisterGameObject(GameObject* pObject); // TODO: Not used, but should be.
    void UnregisterGameObject(int iIndex); // TODO: Not used, but should be.
    Quadrant* GetNeighbour(EQuadrantPos eChunkPosition);
private:
    // std::pair<int,int>
    sf::Vector2f m_TopLeftPosition;
    bool m_bFreezed;
    std::map<EQuadrantPos, Quadrant*> m_NearQuadrants;
    std::vector<GameObject*> m_GameObjects;
    
    sf::Vector2f CalculatePositionForNeighbour(EQuadrantPos eChunkPosition);
};