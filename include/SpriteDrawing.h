#pragma once

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class SpriteDrawing : public IDrawing
{
public:
    SpriteDrawing(std::string ressource_path);
	void Update();
	void Draw(sf::RenderWindow* window);
protected:
	sf::Sprite* Sprite;
	sf::Texture* Texture;
};
