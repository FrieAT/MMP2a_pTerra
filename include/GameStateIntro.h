/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IInputObserver.h"
#include "IGameState.h"

class GameStateIntro : public IGameState, public IInputObserver
{
public:
    ~GameStateIntro();
    void Init();
    void OnInputUpdate(std::string strEvent);
protected:
    bool m_bKeyPressed;
};