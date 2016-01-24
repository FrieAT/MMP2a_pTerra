/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IGameState.h"
#include "EGameState.h"

class Game
{
public:
	Game();
    ~Game();
    
    void Start();
	void StoreCurrentState(bool value = true);
    void ChangeState(EGameState GameState);
	bool IsInitialized(EGameState GameState);
    IGameState* GetCurrentState() { return m_pCurrentState; }
	IGameState* GetLastState() { return m_States.back(); }

    static Game* m_pEngine;
    static const int m_iWindowWidth = 1920;
    static const int m_iWindowHeight = 1080;
    static const int m_iFrameRate = 60;
protected:
    sf::RenderWindow* m_pWindow;
    IGameState* m_pCurrentState;
	std::map<EGameState, IGameState*> m_mGameStateStorage;
    std::vector<IGameState*> m_States;
    sf::Image m_Icon;
};