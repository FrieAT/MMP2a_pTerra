#include "PlayerShip.h"

#include "LinearMovement.h"
#include "PixelPosition.h"
#include "SpriteDrawing.h"
#include "ShipMovement.h"
#include "LinearMovement.h"

PlayerShip::PlayerShip()
{
    // PixelPosition pixelPos(sf::Vector2f(0.f,0.f));
    Position = std::shared_ptr<IPosition>(new PixelPosition(sf::Vector2f(40.f,40.f), sf::Vector2f(32.f, 32.f)));
    Movement = std::shared_ptr<IMovement>(new ShipMovement());
    Drawing = std::shared_ptr<IDrawing>(new SpriteDrawing("assets/space_ship.png"));
    
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