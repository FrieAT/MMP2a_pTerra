#include "GameObjectFactory.h"

#include "LinearMovement.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "ShipMovement.h"

GameObject* GameObjectFactory::CreatePlayerShip()
{
	// TODO: Make it possible to change component values / change the whole factory
	GameObject* ship = new GameObject("ship");

	ship->SetComponent(new PixelPosition(sf::Vector2f(40.f, 40.f), sf::Vector2f(32.f, 32.f)));
	ship->SetComponent(new ShipMovement());
	ship->SetComponent(new SpriteDrawing("assets/space_ship.png"));

	return ship;
}
