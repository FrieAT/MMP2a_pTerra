//
//  IInputObserver.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 16.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef IInputObserver_h
#define IInputObserver_h

#include <SFML/Graphics.hpp>

class IInputObserver
{
public:
	virtual void OnInputUpdate(std::string event) = 0;
};

#endif /* IInputObserver */