#pragma once

#include <SFML/Graphics.hpp>

#include "IGameState.h"

class Game
{
public:
	Game();
    ~Game();
    
    void Start();
    void ChangeState(IGameState* state);
    
    static Game* Engine;
    static const int m_iWindowWidth = 800;
    static const int m_iWindowHeight = 600;
protected:
    sf::RenderWindow* window;
    std::vector<IGameState*> states;
    sf::Image icon;
};