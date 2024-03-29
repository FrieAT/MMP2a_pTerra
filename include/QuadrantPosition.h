/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "PixelPosition.h"
#include "IQuadrantObserver.h"
#include "EQuadrantPos.h"

class QuadrantPosition : public IPosition
{
public:
    QuadrantPosition(sf::Vector2f Position, sf::Vector2f Origin);
    void Init();
    void SetPosition(sf::Vector2f Position);
    sf::Vector2f GetPosition();
    void SetRotation(float rotation);
    float GetRotation();
    sf::Vector2f GetCenter();
    void SetOrigin(sf::Vector2f Origin);
    sf::Vector2f GetOrigin();
    
    Quadrant* GetQuadrant();
    EQuadrantPos GetDirectionKeyFromPos(sf::Vector2f Position);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("QuadrantPosition"); }
private:
    Quadrant* m_pQuadrant;
    EQuadrantPos m_ELastDirection;
};