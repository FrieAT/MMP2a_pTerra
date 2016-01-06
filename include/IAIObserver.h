/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

class IAIObserver
{
public:
	~IAIObserver() { }
	virtual void Update() = 0;
};