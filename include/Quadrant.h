/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

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
    Quadrant* GetNeighbour(EQuadrantPos eChunkPosition, bool bActive, int uChunkDepth = -1);
    int m_bCurrentlyVisited;
private:
    std::pair<int,int> m_Index;
    sf::Vector2f m_TopLeftPosition;
    bool m_bFreezed;
    std::vector<GameObject*> m_GameObjects;
    
    sf::Vector2f CalculatePositionForNeighbour(EQuadrantPos eChunkPosition);
};