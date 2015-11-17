//
//  EventManager.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef EventManager_h
#define EventManager_h

#include <SFML/Graphics.hpp>
#include <memory>
#include "IEventObserver.h"

class EventManager
{
public:
    static void Update(sf::RenderWindow &window);
    
    static void RegisterEventObserver(IEventObserver &observer);
    static void UnregisterEventObserver(IEventObserver &observer);
    
private:
    static std::vector<std::shared_ptr<IEventObserver>> Observers;
    static void UpdateEventObserver(sf::Event event);
};

#endif /* EventManager_h */
