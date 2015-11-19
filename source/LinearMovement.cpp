#include "LinearMovement.h"
#include "GameObject.h"
#include "IPosition.h"

LinearMovement::LinearMovement()
	: MovementX(0.f)
	, MovementY(0.f)
{
	InputManager::RegisterEventObserver(this);
	FrameManager::RegisterEventObserver(this);
}

void LinearMovement::MoveVector(sf::Vector2f &Vector)
{
	auto PositionComponent = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (PositionComponent == NULL)
	{
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


void LinearMovement::OnInputUpdate(std::string event)
{

	bool movementXChanged = false, movementYChanged = false;
	auto pos = std::static_pointer_cast<IPosition>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	std::cout << "x: " <<pos->GetPosition().x << "   y: " << pos->GetPosition().y << std::endl;


	std::string key_state = event.substr(event.length() - 1, 1);
	   if(key_state=="R")
	   {
	       if(!movementYChanged && (event == "UP_R" || event == "DOWN_R"))
		   {
	           this->MovementY = 0;
	       }
		   else if(!movementXChanged && (event == "LEFT_R" || event == "RIGHT_R"))
		   {
	           this->MovementX = 0;
	       }
	   }
	   
	   if(key_state == "P")
	   {
	       if(event == "UP_P" || event == "DOWN_P")
		   {
	           movementYChanged = true;
	           if(event == "UP_P") this->MovementY = -1;
	           else if(event == "DOWN_P") this->MovementY = 1;
	       }
	       
	       if(event == "LEFT_P" || event == "RIGHT_P")
		   {
	           movementXChanged = true;
	           if(event == "LEFT_P") this->MovementX = -1;
	           else if(event == "RIGHT_P") this->MovementX = 1;
	       }
	   }
}
