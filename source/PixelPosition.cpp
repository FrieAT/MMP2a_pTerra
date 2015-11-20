#include "PixelPosition.h"

void PixelPosition::SetPosition(sf::Vector2f Position)
{
	this->Position = Position;
}
sf::Vector2f PixelPosition::GetPosition()
{
	return (this->Position);
}

float PixelPosition::GetRotation()
{
	return Rotation;
}

void PixelPosition::SetOrigin(sf::Vector2f Origin)
{
	this->Origin = Origin;
}

sf::Vector2f PixelPosition::GetOrigin()
{
	return Origin;
}

void PixelPosition::SetRotation(float rotation)
{
	Rotation = rotation;
}
