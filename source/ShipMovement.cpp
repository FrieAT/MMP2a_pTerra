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
}

void ShipMovement::OnInputUpdate(std::string event)
{
	std::string key_state = event.substr(event.length() - 1, 1);
	if(event=="RIGHT_P")
	{
		//pos->SetRotation(pos->GetRotation() + 1);
	}
	if (event == "LEFT_P")
	{
		//pos->SetRotation(pos->GetRotation() - 1);
	}

}

void ShipMovement::OnFrameUpdate(sf::Time delta_time)
{
}
