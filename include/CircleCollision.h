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
	CircleCollision(float radius, IPosition* pPosition);
	~CircleCollision();
    void Init();
	bool colliding(ICollision* pCollisionBody);
	float m_fRadius;
	IPosition* m_pPosition;
	bool m_bHit;
	void OnFrameDraw(sf::RenderWindow* pWindow);

};