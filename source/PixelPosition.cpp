#include "PixelPosition.h"

void PixelPosition::SetPosition(sf::Vector2f Position)
{
	this->Position = Position;
}
sf::Vector2f PixelPosition::GetPosition()
{
	return (this->Position);
}