/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IGameState.h"

class GameStatePlay : public IGameState
{
public:
    ~GameStatePlay();
    void Init(sf::RenderWindow* pWindow);
	void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow);
void SetLoadGame(std::string strLoadGame);
protected:
    sf::Music* m_pMusic;
    std::string m_strLoadGame;
};