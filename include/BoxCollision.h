/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "ICollision.h"
#include "PixelPosition.h"
#include "FrameManager.h"
#include "IFrameObserver.h"

class BoxCollision : public ICollision, public IFrameObserver
{
public:
	BoxCollision(float fWidth, float fHeight, IPosition* pos);
	~BoxCollision();
	bool colliding(ICollision* Collidingbody);
	float m_fWidth;
	float m_fHeight;
	IPosition* pos;
	bool hit;
	void OnFrameDraw(sf::RenderWindow* pWindow);

};