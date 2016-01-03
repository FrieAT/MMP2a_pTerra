/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class SpriteDrawing : public IDrawing
{
public:
    SpriteDrawing(std::string strRessourcePath);
    SpriteDrawing(std::string strRessourcePath, sf::Vector2f ScaleToSize);
    SpriteDrawing(SerializeNode* pNode);
    ~SpriteDrawing();
    void Update();
	void Draw(sf::RenderWindow* pWindow);
    void SetTextureArea(sf::FloatRect Area);
    sf::FloatRect GetTextureArea();
    void Serialize(SerializeNode* pParentNode);
    std::string GetComponentName() { return std::string("SpriteDrawing"); }
protected:
	sf::Sprite* m_pSprite;
	sf::Texture* m_pTexture;
    std::string m_strResPath;
    sf::Vector2f m_ScaleToSize;
};
