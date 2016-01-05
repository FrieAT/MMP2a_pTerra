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
    ~SpriteDrawing();
    void Update();
	void Draw(sf::RenderWindow* pWindow);
    void SetTextureArea(sf::FloatRect Area);
    void SetUpdateFrameRate(int iFrameRate) { m_iTextureFrameUpdateCount = iFrameRate; }
    void GenerateTextureAreas(int iAmountInX, int iAmountInY);
    sf::FloatRect GetTextureArea();
    void Serialize(SerializeNode* pParentNode);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("SpriteDrawing"); }
protected:
	sf::Sprite* m_pSprite;
	sf::Texture* m_pTexture;
    std::string m_strResPath;
    sf::Vector2f m_ScaleToSize;
    std::vector<sf::IntRect> m_TextureRects;
    int m_iTextureRectsCount;
    int m_iTextureFrameUpdateCount;
    int m_iCurrentFrameCount;
};
