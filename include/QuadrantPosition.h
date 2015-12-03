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
    void SetPosition(sf::Vector2f Position);
    sf::Vector2f GetPosition();
    void SetRotation(float rotation);
    float GetRotation();
    void SetOrigin(sf::Vector2f Origin);
    sf::Vector2f GetOrigin();
    
    Quadrant* GetQuadrant();
    EQuadrantPos GetDirectionKeyFromPos(sf::Vector2f Position);
private:
    Quadrant* m_Quadrant;
    void UpdateQuadrantPosition();
};