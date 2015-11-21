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
    sf::Texture* texture;
    sf::Sprite* sprite;
    sf::Font* font;
    sf::Text* heading;
    sf::Text* information;
    bool KeyPressed;
};