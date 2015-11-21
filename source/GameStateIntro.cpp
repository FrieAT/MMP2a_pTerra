#include "GameStateIntro.h"

#include "Game.h"
#include "InputManager.h"
#include "GameStatePlay.h"

GameStateIntro::~GameStateIntro()
{
    InputManager::UnregisterEventObserver(this);
    
    delete texture;
    delete sprite;
    delete font;
    delete heading;
    delete information;
}

void GameStateIntro::Init()
{
    KeyPressed = false;
    
    InputManager::RegisterEventObserver(this);
    
    // ====== Below decprecated method to create things ======
    
    // Load a sprite to display
    texture = new sf::Texture();
    if (!texture->loadFromFile("assets/intro-bg.jpg"))
    {
        throw new std::runtime_error("Unable to load assets/intro-bg.jpg");
    }
    sprite = new sf::Sprite(*texture);
    
    // Load a font to display
    font = new sf::Font();
    if (!font->loadFromFile("assets/Starjedi.ttf"))
    {
        throw new std::runtime_error("Unable to load assets/Starjedi.ttf");
    }
    
    // Create Heading
    std::string heading_text = "The Space Game";
    heading = new sf::Text();
    heading->setFont(*font);
    heading->setString(heading_text);
    heading->setCharacterSize(24);
    heading->setPosition(280.f, 100.f);
    heading->setColor(sf::Color::White);
    
    // Create Information
    std::string information_text = "-- Press FIRE-Key to start game --";
    information = new sf::Text();
    information->setFont(*font);
    information->setString(information_text);
    information->setCharacterSize(16);
    information->setPosition(230.f, 500.f);
    information->setColor(sf::Color::White);
}

void GameStateIntro::Update(sf::RenderWindow* window)
{
    // Draw the sprite
    window->draw(*sprite);
    
    // Draw texts
    window->draw(*heading);
    window->draw(*information);
}

void GameStateIntro::OnInputUpdate(std::string event)
{
    std::size_t delimiter_pos = event.find('_');
    if(delimiter_pos == std::string::npos) return;
    std::string key = event.substr(0, delimiter_pos);
    std::string state = event.substr(delimiter_pos+1, 1);
    
    if(state == "P" && key == "FIRE" && !KeyPressed)
    {
        // Prevent of double changing states.
        KeyPressed = true;
        Game::Engine->ChangeState(new GameStatePlay());
    }
}