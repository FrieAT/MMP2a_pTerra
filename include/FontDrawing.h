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
protected:
    sf::Font* m_pFont; // TODO: Make of Font a flyweight pattern. Just do it.
    sf::Text* m_pText;
};
