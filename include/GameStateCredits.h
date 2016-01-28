/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IInputObserver.h"
#include "IGameState.h"

class GameStateCredits : public IGameState
{
public:
	~GameStateCredits();
	void Init(sf::RenderWindow* pWindow);
	void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow);
protected:
	
};