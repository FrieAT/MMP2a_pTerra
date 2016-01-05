/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "IGameState.h"

class GameStatePause : public IGameState
{
public:
	~GameStatePause();
	void Init(sf::RenderWindow* pWindow);
	void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow);
};