#pragma once

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class FontDrawing : public IDrawing
{
public:
    FontDrawing(std::string sFontPath, std::string sText, int iCharSize);
    ~FontDrawing();
    void Update();
    void Draw(sf::RenderWindow* window);
protected:
    sf::Font* Font; // TODO: Make of Font a flyweight pattern. Just do it.
    sf::Text* Text;
};
