#include "GameObjectFactory.h"

#include "LinearMovement.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "ShipMovement.h"
#include "ScriptedView.h"

GameObject* GameObjectFactory::CreatePlayerShip()
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* ship = new GameObject("ship");

	ship->SetComponent(new PixelPosition(sf::Vector2f(40.f, 40.f), sf::Vector2f(32.f, 32.f)));
	ship->SetComponent(new ShipMovement());
	ship->SetComponent(new SpriteDrawing("assets/space_ship.png"));

	return ship;
}

GameObject* GameObjectFactory::CreateBackgroundSprite()
{
    // TODO: Make it possible to change component values / change the whole factory
    GameObject* background = new GameObject("background");
    
    background->SetComponent(new PixelPosition(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
    background->SetComponent(new SpriteDrawing("assets/space-map.jpg"));
    // background->SetComponent(new ScriptedView(sf::FloatRect(0, 0, 800, 600), sf::Vector2f(800, 0), 0.05f));
    
    return background;
}