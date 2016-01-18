/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Audio.hpp>

#include "IGameState.h"
#include "EGameState.h"

#include <map>

class Game
{
public:
	Game();
    ~Game();
    
    void Start();
	void StoreCurrentState();
    void ChangeState(EGameState GameState);
	bool IsInitialized(EGameState GameState);
    IGameState* GetCurrentState() { return m_pCurrentState; }
	IGameState* GetLastState() { return m_States.back(); }
    static Game* m_pEngine;
    static int m_iWindowWidth;
    static int m_iWindowHeight;
    static int m_iFrameRate;
protected:
    sf::RenderWindow* m_pWindow;
    IGameState* m_pCurrentState;
	std::map<EGameState, IGameState*> m_mGameStateStorage;
    std::vector<IGameState*> m_States;
    sf::Image m_Icon;
};