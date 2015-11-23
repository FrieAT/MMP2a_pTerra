#include "GameObjectFactory.h"

#include "Game.h"
#include "LinearMovement.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "FontDrawing.h"
#include "ShipMovement.h"
#include "ScriptedView.h"

GameObject* GameObjectFactory::CreatePlayerShip()
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* ship = new GameObject(std::string("ship"));

	ship->SetComponent(new PixelPosition(sf::Vector2f(40.f, 40.f), sf::Vector2f(32.f, 32.f)));
	ship->SetComponent(new ShipMovement());
	ship->SetComponent(new SpriteDrawing("assets/space_ship.png"));

	return ship;
}

GameObject* GameObjectFactory::CreateBackgroundSprite(std::string background_path)
{
    // TODO: Make it possible to change component values / change the whole factory
    GameObject* background = new GameObject(std::string("background"));
    
    background->SetComponent(new PixelPosition(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    background->SetComponent(new SpriteDrawing(background_path));
    
    return background;
}

GameObject* GameObjectFactory::CreateScriptedView()
{
    GameObject* view = new GameObject(std::string("background"));
    
    view->SetComponent(new ScriptedView(sf::FloatRect(0, 0, static_cast<float>(Game::m_iWindowWidth), static_cast<float>(Game::m_iWindowHeight)), sf::Vector2f(1920.f - static_cast<float>(Game::m_iWindowWidth), 0), 20.f));
    
    return view;
}

GameObject* GameObjectFactory::CreateFontText(sf::Vector2f Position, std::string sFontPath, std::string sText, int iCharSize)
{
    GameObject* font_text = new GameObject(std::string(std::string("text")));
    
    font_text->SetComponent(new PixelPosition(Position, sf::Vector2f(0.f, 0.f)));
    font_text->SetComponent(new FontDrawing(sFontPath, sText, iCharSize));
    
    return font_text;
}