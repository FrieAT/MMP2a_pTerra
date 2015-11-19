#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "IGameState.h"

class GameStatePlay : public IGameState
{
public:
    GameStatePlay();
    ~GameStatePlay();
    
    void Update(sf::RenderWindow* window);
    
protected:
    sf::Texture* texture;
    sf::Music* music;
    sf::Sprite* sprite;
};