#include "LinearMovement.h"
#include "GameObject.h"
#include "IPosition.h"

LinearMovement::LinearMovement(float Rotation, sf::Vector2f Shipspeed)
{
	FrameManager::RegisterEventObserver(this);
	sf::Transform rotation_mat = sf::Transform::Identity;
	rotation_mat.rotate(Rotation);
	rotation = Rotation;
	speed = 200.f;
	direction = rotation_mat*(sf::Vector2f(0, -1));
	movement = Shipspeed;
}

LinearMovement::~LinearMovement()
{
    FrameManager::UnregisterEventObserver(this);
}


void LinearMovement::OnFrameUpdate(sf::Time delta_time)
{
	IPosition* pos = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	pos->SetRotation(rotation);
	movement = direction * speed* delta_time.asSeconds();
	pos->SetPosition(pos->GetPosition()+ movement);

}

