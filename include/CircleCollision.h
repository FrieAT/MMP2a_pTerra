/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "ICollision.h"
#include "PixelPosition.h"
#include "FrameManager.h"
#include "IFrameObserver.h"

class CircleCollision : public ICollision, public IFrameObserver
{
public:
	CircleCollision(float radius, IPosition* pos);
	~CircleCollision();
	bool colliding(ICollision* Collidingbody);
	float radius;
	IPosition* pos;
	bool hit;
	void OnFrameDraw(sf::RenderWindow* pWindow);

};