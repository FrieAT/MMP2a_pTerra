//
//  SpriteDrawing.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef SpriteDrawing_h
#define SpriteDrawing_h

#include <SFML/Graphics.hpp>

#include "IDrawing.h"

class SpriteDrawing : public IDrawing
{
public:
    SpriteDrawing(sf::Sprite &Sprite, sf::Texture &Texture);
    void Update();
    void Draw(sf::RenderWindow &window);
protected:
    sf::Sprite* Sprite;
    sf::Texture* Texture;
};

#endif /* SpriteDrawing_h */
