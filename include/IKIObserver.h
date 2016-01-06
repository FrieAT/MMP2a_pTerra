/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

class IKIObserver
{
public:
	~IKIObserver() { }
	virtual void Update() = 0;
};