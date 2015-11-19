#pragma once

#include "IPosition.h"

class PixelPosition : public IPosition
{
public:
	PixelPosition(sf::Vector2f Position) : IPosition(Position) { }
	void SetPosition(sf::Vector2f Position);
	sf::Vector2f GetPosition();
	float GetRotation();
	void SetRotation(float rotation);
private:

};
