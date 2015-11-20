#include "ShipMovement.h"


ShipMovement::ShipMovement()
{
	//auto component = GetAssignedGameObject()->GetComponent(EComponentType::Position);
	//pos = std::static_pointer_cast<IPosition>(component);
	InputManager::RegisterEventObserver(this);
	FrameManager::RegisterEventObserver(this);
}


ShipMovement::~ShipMovement()
{
}

void ShipMovement::MoveVector(sf::Vector2f & Vector)
{
	auto pos = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	sf::Transform rotation_mat = sf::Transform::Identity;
	rotation_mat.rotate(pos->GetRotation());


}

void ShipMovement::OnInputUpdate(std::string event)
{
	auto pos = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	std::string key_state = event.substr(event.length() - 1, 1);
	if(event=="RIGHT_P")
	{
		pos->SetRotation(pos->GetRotation() + 1);
	}
	if (event == "LEFT_P")
	{
		pos->SetRotation(pos->GetRotation() - 1);
	}
	if (event == "UP_P")
	{
		MoveVector(sf::Vector2i(1, 1));
	}
}

void ShipMovement::OnFrameUpdate(sf::Time delta_time)
{
	auto pos = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	pos->SetPosition(pos->GetPosition() + direction);
}
