//
//  FrameManager.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef FrameManager_h
#define FrameManager_h

#include <SFML/Graphics.hpp>
#include <memory>
#include "IFrameObserver.h"

class FrameManager 
{
public:
    static void Update(sf::RenderWindow &window);
    static void RegisterEventObserver(IFrameObserver &observer);
    static void UnregisterEventObserver(IFrameObserver &observer);
private:
    static sf::Clock clock_time;
    static std::vector<std::shared_ptr<IFrameObserver>> Observers;
    static void UpdateEventObserver(sf::Time delta_time);
};

#endif /* FrameManager_h */
