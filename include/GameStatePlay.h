#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "IGameState.h"

class GameStatePlay : public IGameState
{
public:
    // GameStatePlay();
    ~GameStatePlay();
    void Init();
    void Update(sf::RenderWindow* window);
    
protected:
    sf::Music* music;
    sf::Texture* texture;
    sf::Sprite* sprite;
};