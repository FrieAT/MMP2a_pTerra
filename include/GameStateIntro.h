#pragma once

#include <SFML/Graphics.hpp>

#include "IGameState.h"

class GameStateIntro : public IGameState
{
public:
    ~GameStateIntro();
    void Init();
    void Update(sf::RenderWindow* window);
protected:
    sf::Texture* texture;
    sf::Sprite* sprite;
};