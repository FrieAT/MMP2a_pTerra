#pragma once

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class SpriteDrawing : public IDrawing
{
public:
	SpriteDrawing(sf::Sprite &Sprite, sf::Texture &Texture);
	void Update();
	void Draw(sf::RenderWindow* window);
protected:
	sf::Sprite* Sprite;
	sf::Texture* Texture;
};
