#include "ShipMovement.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"

ShipMovement::ShipMovement(char Player)
{
	//auto component = GetAssignedGameObject()->GetComponent(EComponentType::Position);
	//pos = std::static_pointer_cast<IPosition>(component);
	InputManager::RegisterEventObserver(this);
	FrameManager::RegisterEventObserver(this);
	this->Player = Player;

	Impulses.resize(5);
	Acceleration = 1.f;
	Max_Speed = 11000;
}


ShipMovement::~ShipMovement()
{
    InputManager::UnregisterEventObserver(this);
    FrameManager::UnregisterEventObserver(this);
}


void ShipMovement::OnInputUpdate(std::string event)
{
	IPosition* pos = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (event[0] == Player)
	{
		event = event.substr(1);
	}
	else return;


	if(event=="RIGHT_P")
	{
		pos->SetRotation(pos->GetRotation() + 5);
	}
	if (event == "LEFT_P")
	{
		pos->SetRotation(pos->GetRotation() - 5);
	}
	if (event == "UP_P")
	{
		direction = sf::Vector2f(0.f, -0.8f);
	}
	if (event == "DOWN_P")
	{
		direction = sf::Vector2f(0.f, 0.6f);
	}

	if (event == "UP_R" || event == "DOWN_R")
	{
		direction = sf::Vector2f(0.f, 0.f);
	}

	//TODO make a own weapon component
	if (event == "FIRE_P")
	{
  		ObjectManager::AddGameObject(GameObjectFactory::CreateMissile(pos,Impulses[0]));
	}
}


void ShipMovement::update_movement()
{
	IPosition* pos = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	sf::Transform rotation_mat = sf::Transform::Identity;
	rotation_mat.rotate(pos->GetRotation());

	Impulses[0] = Impulses[0] + rotation_mat * direction * Acceleration;

	float speed = Impulses[0].x*Impulses[0].x + Impulses[0].y * Impulses[0].y;

	if (speed >= Max_Speed)
	{
		Impulses[0] = Impulses[0] * 0.99f;
	}

	//std::cout << speed << std::endl;

}



void ShipMovement::OnFrameUpdate(sf::Time delta_time)
{
	IPosition* pos = (IPosition*)(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	sf::Vector2f movement;

	update_movement();

	for (int i = 0; i < Impulses.size();i++)
	{
		movement += Impulses[i];
	}

	pos->SetPosition(pos->GetPosition() + movement * delta_time.asSeconds());

}
