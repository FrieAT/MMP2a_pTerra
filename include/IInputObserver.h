#pragma once

#include <SFML/Graphics.hpp>

class IInputObserver
{
public:
	virtual void OnInputUpdate(std::string event) = 0;
};