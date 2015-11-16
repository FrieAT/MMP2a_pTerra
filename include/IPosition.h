//
//  IPosition.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IPosition_h
#define IPosition_h

#include <SFML/Graphics.hpp>

#include "IComponent.h"

class IPosition : public IComponent
{
public:
    IPosition(sf::Vector2f Position) {
        this->Position = Position;
    }
    virtual void SetPosition(sf::Vector2f Position) = 0;
    virtual sf::Vector2f GetPosition() = 0;
    
    EComponentType GetComponentType() { return EComponentType::Position; }
protected:
    sf::Vector2f Position;
};

#endif /* IPosition_h */
