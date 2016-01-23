/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "IInputObserver.h"
#include "IGameState.h"

class GameStateGameOver : public IGameState, public IInputObserver
{
public:
    ~GameStateGameOver();
    void Init(sf::RenderWindow* pWindow);
	void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow);
    void OnInputUpdate(std::string strEvent);
protected:
    bool m_bKeyPressed;
};