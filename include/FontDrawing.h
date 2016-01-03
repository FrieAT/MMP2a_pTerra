/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class FontDrawing : public IDrawing
{
public:
    FontDrawing(std::string strFontPath, std::string strText, int iCharSize);
    ~FontDrawing();
    void Update();
    void Draw(sf::RenderWindow* pWindow);
    void SetTextureArea(sf::FloatRect Area);
    sf::FloatRect GetTextureArea();
    void SetText(std::string strText);
    void Serialize(SerializeNode* pParentNode);
    std::string GetComponentName() { return std::string("FontDrawing"); }
protected:
    sf::Font* m_pFont; // TODO: Make of Font a flyweight pattern. Just do it.
    sf::Text* m_pText;
    std::string m_strResPath;
    std::string m_strText;
    int m_iCharSize;
};
