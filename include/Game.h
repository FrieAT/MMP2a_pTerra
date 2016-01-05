/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Audio.hpp>

#include "IGameState.h"

class Game
{
public:
	Game();
    ~Game();
    
    void Start();
    void ChangeState(IGameState* pState);
    
    static Game* m_pEngine;
    static const int m_iWindowWidth = 1920;
    static const int m_iWindowHeight = 1080;
protected:
    sf::RenderWindow* m_pWindow;
    IGameState* m_pCurrentState;
    std::vector<IGameState*> m_States;
    sf::Image m_Icon;
};