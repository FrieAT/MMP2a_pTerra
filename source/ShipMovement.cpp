/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "ShipMovement.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"
#include "SpriteDrawing.h"
#include "IEngine.h"
#include "Game.h"

ShipMovement::ShipMovement(char cPlayer)
{
	this->m_cPlayer = cPlayer;
	mass = 3;
	invMass = 1 / mass;

	m_ShipState = std::vector<bool>(5, false);
	m_fSpeed = 2100.f;
	m_fMaxSpeed = 1200;
	m_fFirerate = 0.4f;
    m_fWeaponcoolDown = 0.f;
}

ShipMovement::~ShipMovement()
{
    InputManager::GetInstance().UnregisterEventObserver(this);
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void ShipMovement::Init()
{
    InputManager::GetInstance().RegisterEventObserver(this);
    FrameManager::GetInstance().RegisterEventObserver(this);
}


void ShipMovement::OnInputUpdate(std::string strEvent)
{
	if (strEvent == "RIGHT_P")
	{
		m_ShipState[0] = true;
	}
	if (strEvent == "RIGHT_R")
	{
		m_ShipState[0] = false;
	}


	if (strEvent == "LEFT_P")
	{
		m_ShipState[1] = true;
	}
	if (strEvent == "LEFT_R")
	{
		m_ShipState[1] = false;
	}


	if (strEvent == "UP_P")
	{
		m_ShipState[2] = true;
	}
	if (strEvent == "UP_R")
	{
		m_ShipState[2] = false;
	}


	if (strEvent == "DOWN_P")
	{
		m_ShipState[3] = true;
	}
	if (strEvent == "DOWN_R")
	{
		m_ShipState[3] = false;
	}


	//TODO make a own weapon component
	if (strEvent == "FIRE_P")
	{
		m_ShipState[4] = true;
	}
	if (strEvent == "FIRE_R")
	{
		m_ShipState[4] = false;
	}
}


void ShipMovement::UpdateMovement(sf::Time DeltaTime)
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	const float fFuelDrainForForward = 15.0f * DeltaTime.asSeconds();
	const float fFuelDrainForBackward = 12.0f * DeltaTime.asSeconds();
	const float fFuelDrainForMissile = 25.0f;

	if(m_ShipState[0]) pPositionComponent->SetRotation(pPositionComponent->GetRotation() + 60*(Game::m_pEngine->m_bRotateCamera ? 1 : 3)*DeltaTime.asSeconds());	//rotate right
	if (m_ShipState[1]) pPositionComponent->SetRotation(pPositionComponent->GetRotation() - 60*(Game::m_pEngine->m_bRotateCamera ? 1 : 3)*DeltaTime.asSeconds()); //rotate left
	if (m_ShipState[2])
	{
		IEngine* pEngine = static_cast<IEngine*>(GetAssignedGameObject()->GetComponent(EComponentType::Engine));
		if (pEngine != nullptr && pEngine->GetFuel() >= fFuelDrainForForward)
		{
			pEngine->AddFuel(-fFuelDrainForForward);
			m_Direction = sf::Vector2f(0.f, -0.8f); //move forward
		}
		else
		{
			m_ShipState[2] = false;
		}
	}
	if (m_ShipState[3])
	{
		IEngine* pEngine = static_cast<IEngine*>(GetAssignedGameObject()->GetComponent(EComponentType::Engine));
		if (pEngine != nullptr && pEngine->GetFuel() >= fFuelDrainForBackward)
		{
			pEngine->AddFuel(-fFuelDrainForBackward);
			m_Direction = sf::Vector2f(0.f, 0.6f); //move backward
		}
		else
		{
			m_ShipState[3] = false;
		}
	}
	if (!m_ShipState[2]&& !m_ShipState[3]) m_Direction = sf::Vector2f(0.f, 0.f); //turn off thruster
	if (m_ShipState[4] && m_fWeaponcoolDown <= 0.f)		//fire
	{
		IEngine* pEngine = static_cast<IEngine*>(GetAssignedGameObject()->GetComponent(EComponentType::Engine));
		if (pEngine != nullptr && pEngine->GetFuel() >= fFuelDrainForMissile)
		{
			pEngine->AddFuel(-fFuelDrainForMissile);
			m_fWeaponcoolDown = m_fFirerate;
			GameObject* pMissile = GameObjectFactory::CreateMissile(GetAssignedGameObject(), pPositionComponent, velocity); //shoot rockets
			pMissile->SetTemporaryState(true);
			//std::cout << velocity.x << " "<<velocity.y << std::endl;
		}
	}
	if (m_fWeaponcoolDown > 0.f)
    {
        m_fWeaponcoolDown -= 1.f * DeltaTime.asSeconds();
    }

	//if (fSpeed >= m_fMaxSpeed)
	//{
	//	m_Impulses[0] = m_Impulses[0] * 0.99f;
	//}

	//std::cout << speed << std::endl;

}


void ShipMovement::OnFrameUpdate(sf::Time DeltaTime)
{
	UpdateMovement(DeltaTime);
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	sf::Vector2f forces;

	sf::Transform RotationMatrix = sf::Transform::Identity;
	RotationMatrix.rotate(pPositionComponent->GetRotation());

	sf::Vector2f accVec = RotationMatrix * m_Direction *m_fSpeed;

	auto length2 = [](const sf::Vector2f &vec) -> float { return vec.x * vec.x + vec.y * vec.y; };	//calculate vectorlenght squared

	float squaredSpeedLimit = m_fMaxSpeed * m_fMaxSpeed;
	if (length2(velocity + accVec * DeltaTime.asSeconds()) < squaredSpeedLimit)
		impulses.push_back(accVec);

	for (const auto& f : impulses)
		forces += f;
	impulses.clear();

	acceleration = forces * invMass;
	velocity += acceleration * DeltaTime.asSeconds();
	//body.velocity = body.velocity * 0.99f; //< simple "friction"

	pPositionComponent->SetPosition(pPositionComponent->GetPosition() + velocity * DeltaTime.asSeconds());

    // Set Animation for thrusters
    SpriteDrawing* pSpriteComponent = static_cast<SpriteDrawing*>(GetAssignedGameObject()->GetComponent(EComponentType::Drawing));
    if(pSpriteComponent != nullptr)
    {
        if(m_Direction.y != 0)
        {
            pSpriteComponent->GenerateTextureAreas(0, 0);
            pSpriteComponent->SetTextureArea(sf::FloatRect(64.f, 0.f, 64.f, 102.f));
            pSpriteComponent->SetTextureArea(sf::FloatRect(128.f, 0.f, 64.f, 102.f));
        }
        else
        {
            pSpriteComponent->GenerateTextureAreas(0, 0);
            pSpriteComponent->SetTextureArea(sf::FloatRect(0.f, 0.f, 64.f, 102.f));
        }
    }
}

void ShipMovement::Serialize(SerializeNode *pParentNode)
{
    this->IMovement::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("ControlID", ESerializeNodeType::Property, std::to_string(m_cPlayer)));
    pParentNode->AddElement(new SerializeNode("Speed", ESerializeNodeType::Property, std::to_string(m_fSpeed)));
    pParentNode->AddElement(new SerializeNode("MaxSpeed", ESerializeNodeType::Property, std::to_string(m_fMaxSpeed)));
    pParentNode->AddElement(new SerializeNode("Firerate", ESerializeNodeType::Property, std::to_string(m_fFirerate)));
    pParentNode->AddElement(new SerializeNode("WeaponCooldown", ESerializeNodeType::Property, std::to_string(m_fWeaponcoolDown)));
    pParentNode->AddElement(new SerializeNode("DirectionX", ESerializeNodeType::Property, std::to_string(m_Direction.x)));
    pParentNode->AddElement(new SerializeNode("DirectionY", ESerializeNodeType::Property, std::to_string(m_Direction.y)));
    SerializeNode *pNodeStates = new SerializeNode("ShipStates", ESerializeNodeType::List);
    auto it = m_ShipState.begin();
    unsigned count = 0;
    while(it != m_ShipState.end())
    {
        pNodeStates->AddElement(new SerializeNode(std::to_string(count), ESerializeNodeType::Property, std::to_string((*it))));
        it++;
        count++;
    }
    pParentNode->AddElement(pNodeStates);
}

IComponent* ShipMovement::Deserialize(SerializeNode* pNode)
{
    ShipMovement* pComponent = new ShipMovement('0');
    
    IMovement::Deserialize(pNode, pComponent);
    
    float x, y;
    
    pComponent->m_cPlayer = stoi((pNode->GetNode("ControlID"))->GetValue());
    pComponent->m_fSpeed = stof((pNode->GetNode("Speed"))->GetValue());
    pComponent->m_fMaxSpeed = stof((pNode->GetNode("MaxSpeed"))->GetValue());
    pComponent->m_fFirerate = stof((pNode->GetNode("Firerate"))->GetValue());
    pComponent->m_fWeaponcoolDown = stof((pNode->GetNode("WeaponCooldown"))->GetValue());
    
    x = stof((pNode->GetNode("DirectionX"))->GetValue());
    y = stof((pNode->GetNode("DirectionY"))->GetValue());
    pComponent->m_Direction = sf::Vector2f(x, y);
    
    SerializeNode* pNodeShipStates = pNode->GetNode("ShipStates");
    unsigned int count = 0;
    do
    {
        SerializeNode* pCurrentNode = pNodeShipStates->GetNode(std::to_string(count++));
        if(pCurrentNode == nullptr)
        {
            pNodeShipStates = nullptr;
            continue;
        }
		int iShipState = stoi(pCurrentNode->GetValue());
        pComponent->m_ShipState.push_back((iShipState ? true : false));
    } while(pNodeShipStates != nullptr);
    
    return pComponent;
}

void ShipMovement::setShipState(int State, bool value)
{
	m_ShipState[State] = value;
}

bool ShipMovement::getShipState(int State)
{
	return m_ShipState[State];
}

void ShipMovement::SetMass(float mass) {
	this->mass = mass;
	this->invMass = 1 / mass;

}

void ShipMovement::SetFirerate(float Firerate)
{
	m_fFirerate = Firerate;
}
