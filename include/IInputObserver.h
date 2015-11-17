#pragma once

#include <SFML/Graphics.hpp>

class IInputObserver
{
public:
	virtual void OnInputUpdate(sf::Event event) = 0;
};