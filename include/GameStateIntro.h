#pragma once

#include <SFML/Graphics.hpp>

#include "IInputObserver.h"
#include "IGameState.h"

class GameStateIntro : public IGameState, public IInputObserver
{
public:
    ~GameStateIntro();
    void Init();
    void Update(sf::RenderWindow* window);
    void OnInputUpdate(std::string event);
protected:
    bool KeyPressed;
};