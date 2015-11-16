//
//  IDrawing.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IDrawing_h
#define IDrawing_h

#include <SFML/Graphics.hpp>

#include "IComponent.h"
#include "IFrameObserver.h"

class IDrawing : public IComponent
{
public:
    virtual void Draw(sf::RenderWindow &window) = 0;
    virtual void Update() = 0;
    EComponentType GetComponentType() { return EComponentType::Drawing; }
    
private:
    
};

#endif /* IDrawing_h */
