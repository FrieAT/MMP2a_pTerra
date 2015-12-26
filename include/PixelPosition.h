/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IPosition.h"

class PixelPosition : public IPosition
{
public:
    PixelPosition(sf::Vector2f Position, sf::Vector2f Origin);
	void SetPosition(sf::Vector2f Position);
	sf::Vector2f GetPosition();
	sf::Vector2f GetCenter();
	void SetRotation(float rotation);
	float GetRotation();
	void SetOrigin(sf::Vector2f Origin);
	sf::Vector2f GetOrigin();
    Quadrant* GetQuadrant();
private:
    Quadrant* m_pQuadrant;
    void UpdateQuadrantPosition();
};
