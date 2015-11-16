#include "LinearMovement.h"
#include "GameObject.h"
#include "IPosition.h"

LinearMovement::LinearMovement()
: MovementX(0.f)
, MovementY(0.f)
{
    EventManager::RegisterEventObserver(*this);
    FrameManager::RegisterEventObserver(*this);
}

void LinearMovement::MoveVector(sf::Vector2f &Vector)
{
    auto PositionComponent = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    if(PositionComponent == NULL) {
        return; // TODO: NullReferenceException when Position Component is missing for GameObject
    }
    sf::Vector2f Pos = PositionComponent->GetPosition();
    Pos.x += Vector.x;
    Pos.y += Vector.y;
    PositionComponent->SetPosition(Pos);
}

void LinearMovement::OnFrameUpdate(sf::Time delta_time)
{
    sf::Vector2f moveVector(this->MovementX, this->MovementY);
    moveVector *= 100.f * delta_time.asSeconds();
    this->MoveVector(moveVector);
}

void LinearMovement::OnEventUpdate(sf::Event event)
{
    bool movementXChanged = false, movementYChanged = false;
    
    if(event.type == sf::Event::KeyReleased) {
        if(!movementYChanged && (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)) {
            this->MovementY = 0;
        } else if(!movementXChanged && (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)) {
            this->MovementX = 0;
        }
    }
    
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S) {
            movementYChanged = true;
            if(event.key.code == sf::Keyboard::W) this->MovementY = -1;
            else if(event.key.code == sf::Keyboard::S) this->MovementY = 1;
        }
        
        if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
            movementXChanged = true;
            if(event.key.code == sf::Keyboard::A) this->MovementX = -1;
            else if(event.key.code == sf::Keyboard::D) this->MovementX = 1;
        }
    }
}