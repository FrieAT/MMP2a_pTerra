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
	BoxCollision(float fWidth, float fHeight);
	~BoxCollision();
    void Init();
	bool colliding(ICollision* pCollisionBody);
	float m_fWidth;
	float m_fHeight;
	bool m_bHit;
	void OnFrameDraw(sf::RenderWindow* pWindow);

};