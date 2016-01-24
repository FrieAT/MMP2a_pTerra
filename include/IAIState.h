/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "GameObject.h"

class IAIState
{
public:
	IAIState() { }
	virtual ~IAIState() { }
	virtual void Update(GameObject* obj) = 0;
};