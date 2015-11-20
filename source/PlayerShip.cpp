#include "PlayerShip.h"

#include "LinearMovement.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "ShipMovement.h"
#include "LinearMovement.h"

PlayerShip::PlayerShip()
: Position(new PixelPosition(sf::Vector2f(20.f,20.f)))
, Movement(new LinearMovement())
, Drawing(new SpriteDrawing("assets/space_ship.png"))
{
    SetComponent(Position);
    SetComponent(Movement);
    SetComponent(Drawing);
}

PlayerShip::~PlayerShip()
{
    RemoveComponent(EComponentType::Position);
    RemoveComponent(EComponentType::Movement);
    RemoveComponent(EComponentType::Drawing);
}