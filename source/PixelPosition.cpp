//
//  LinearMovement.cpp
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#include "PixelPosition.h"

void PixelPosition::SetPosition(sf::Vector2f Position)
{
    this->Position = Position;
}
sf::Vector2f PixelPosition::GetPosition()
{
    return (this->Position);
}