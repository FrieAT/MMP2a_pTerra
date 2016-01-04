/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "IGameState.h"

class GameStatePlay : public IGameState
{
public:
    ~GameStatePlay();
    void Init();
    void SetLoadGame(std::string strLoadGame);
protected:
    sf::Music* m_pMusic;
    std::string m_strLoadGame;
};