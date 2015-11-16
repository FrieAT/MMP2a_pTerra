//
//  PlayerShip.cpp
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#include "PlayerShip.h"


#include "LinearMovement.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"

PlayerShip::PlayerShip()
{
    // PixelPosition pixelPos(sf::Vector2f(0.f,0.f));
    PixelPosition* pixelPos = new PixelPosition(sf::Vector2f(20.f,20.f));
    
    LinearMovement* movement = new LinearMovement();
    
    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile("assets/space_ship.png")) {
        throw std::exception();
    }
    SpriteDrawing* sprite = new SpriteDrawing(*new sf::Sprite(*texture), *texture);
    
    SetComponent(std::shared_ptr<IComponent>(pixelPos));
    SetComponent(std::shared_ptr<IComponent>(movement));
    SetComponent(std::shared_ptr<IComponent>(sprite));
}