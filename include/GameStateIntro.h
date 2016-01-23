/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IInputObserver.h"
#include "IGameState.h"

class GameStateIntro : public IGameState, public IInputObserver
{
public:
    ~GameStateIntro();
    void Init(sf::RenderWindow* pWindow);
	void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow);
    void OnInputUpdate(std::string strEvent);
protected:
    bool m_bKeyPressed = false;
	bool m_bExit = false;
};