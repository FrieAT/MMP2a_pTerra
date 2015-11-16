//
//  IManager.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IManager_h
#define IManager_h

#include <memory>

#include <SFML/Graphics.hpp>

class IManager
{
public:
    static void Update(sf::RenderWindow &window);
};

#endif /* IManager_h */
