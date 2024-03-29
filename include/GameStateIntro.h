/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IInputObserver.h"
#include "IGameState.h"

class GameStateIntro : public IGameState
{
public:
    ~GameStateIntro();
    void Init(sf::RenderWindow* pWindow);
	void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow);
protected:
	bool m_bExit = false;
};