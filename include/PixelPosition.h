/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IPosition.h"

class PixelPosition : public IPosition
{
public:
	PixelPosition(sf::Vector2f Position, sf::Vector2f Origin) : IPosition(Position,Origin) { }
	void SetPosition(sf::Vector2f Position);
	sf::Vector2f GetPosition();
	void SetRotation(float rotation);
	float GetRotation();
	void SetOrigin(sf::Vector2f Origin);
	sf::Vector2f GetOrigin();
private:

};
