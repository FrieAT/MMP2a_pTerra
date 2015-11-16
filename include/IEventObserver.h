//
//  IEventObserver.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IEventObserver_h
#define IEventObserver_h

#include <SFML/Graphics.hpp>

class IEventObserver
{
public:
    virtual void OnEventUpdate(sf::Event event) = 0;
};

#endif /* IEventObserver_h */
