#include "GameStateIntro.h"

#include "InputManager.h"

GameStateIntro::~GameStateIntro()
{
    delete texture;
    delete sprite;
}

void GameStateIntro::Init()
{
    // ====== Below decprecated method to create things ======
    
    // Load a sprite to display
    texture = new sf::Texture();
    if (!texture->loadFromFile("assets/intro-bg.jpg"))
    {
        throw new std::runtime_error("Unable to load assets/intro-bg.jpg");
    }
    sprite = new sf::Sprite(*texture);
}

void GameStateIntro::Update(sf::RenderWindow* window)
{
    // Draw the sprite
    window->draw(*sprite);
}