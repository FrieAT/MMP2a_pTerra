//
//  LinearMovement.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef PixelPosition_h
#define PixelPosition_h

#include "IPosition.h"

class PixelPosition : public IPosition
{
public:
    PixelPosition(sf::Vector2f Position) : IPosition(Position) { }
    void SetPosition(sf::Vector2f Position);
    sf::Vector2f GetPosition();
private:
    
};

#endif /* PixelPosition_h */
