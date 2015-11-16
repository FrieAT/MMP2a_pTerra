//
//  IFrameObserver.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IFrameObserver_h
#define IFrameObserver_h

#include <SFML/Graphics.hpp>

class IFrameObserver
{
public:
    virtual void OnFrameUpdate(sf::Time delta_time) = 0;
};

#endif /* IFrameObserver_h */
