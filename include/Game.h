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
protected:
    sf::RenderWindow* window;
    std::vector<IGameState*> states;
    sf::Image icon;
};