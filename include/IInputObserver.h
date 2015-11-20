#pragma once

#include <SFML/Graphics.hpp>

class IInputObserver
{
public:
    ~IInputObserver() { }
	virtual void OnInputUpdate(std::string event) = 0;
};