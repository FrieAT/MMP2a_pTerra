/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class SpriteDrawing : public IDrawing
{
public:
    SpriteDrawing(std::string& strRessourcePath);
    SpriteDrawing(std::string& strRessourcePath, sf::Vector2f& ScaleToSize);
    ~SpriteDrawing();
    void Update();
	void Draw(sf::RenderWindow* pWindow);
protected:
	sf::Sprite* m_pSprite;
	sf::Texture* m_pTexture;
};
