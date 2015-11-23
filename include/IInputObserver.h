/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

class IInputObserver
{
public:
    ~IInputObserver() { }
	virtual void OnInputUpdate(std::string strEvent) = 0;
};