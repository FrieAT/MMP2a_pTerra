/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "ICollision.h"
#include "PixelPosition.h"

class CircleCollision : public ICollision
{
public:
	CircleCollision(float radius, PixelPosition pos);
	~CircleCollision();
	bool colliding(ICollision* Collidingbody);
	float radius;
	PixelPosition pos;
};