//
//  EventManager.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef InputMangager_h
#define InputMangager_h

#include <SFML/Graphics.hpp>
#include <memory>
#include "IInputObserver.h"


class InputManager
{
public:
	InputManager();
	static void Update(sf::RenderWindow &window);
	static void RegisterEventObserver(IInputObserver &observer);
	static void UnregisterEventObserver(IInputObserver &observer);

private:
	static std::vector<std::shared_ptr<IInputObserver>> Observers;
	static void UpdateEventObserver(std::string event);
};

#endif/*InputMangager_h*/
