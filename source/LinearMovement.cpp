#include "LinearMovement.h"
#include "GameObject.h"
#include "IPosition.h"

LinearMovement::LinearMovement(float Rotation, sf::Vector2f Shipspeed)
{
	FrameManager::GetInstance().RegisterEventObserver(this);
	sf::Transform rotation_mat = sf::Transform::Identity;
	rotation_mat.rotate(Rotation);
	rotation = Rotation;
	speed = 5.f;
	direction = rotation_mat*(sf::Vector2f(0, -5)) + Shipspeed;
}

LinearMovement::~LinearMovement()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
}


void LinearMovement::OnFrameUpdate(sf::Time delta_time)
{
	IPosition* pos = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	pos->SetRotation(rotation);
	pos->SetPosition(pos->GetPosition() + direction * speed* delta_time.asSeconds());

}

