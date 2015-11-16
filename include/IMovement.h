//
//  IMovement.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IMovement_h
#define IMovement_h

#include "IComponent.h"

class IMovement : public IComponent
{
public:
    virtual void MoveVector(sf::Vector2f &Vector) = 0;
    
    EComponentType GetComponentType() { return EComponentType::Movement; }
protected:
    sf::Clock deltaClock;
};

#endif /* IMovement_h */
