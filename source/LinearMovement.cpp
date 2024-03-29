/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "LinearMovement.h"
#include "GameObject.h"
#include "IPosition.h"

//LinearMovement::LinearMovement(float fRotation, sf::Vector2f ShipSpeed)
//{
//	FrameManager::GetInstance().RegisterEventObserver(this);
//	sf::Transform RotationMatrix = sf::Transform::Identity;
//	RotationMatrix.rotate(fRotation);
//	m_fRotation = fRotation;
//	m_fSpeed = 100.f;
//	m_Direction = RotationMatrix*(sf::Vector2f(0, -1));
//	mass = 5;
//	invMass = 1 / mass;
//}
//
//LinearMovement::LinearMovement(float fRotation, float fSpeed)
//{
//	FrameManager::GetInstance().RegisterEventObserver(this);
//	sf::Transform RotationMatrix = sf::Transform::Identity;
//	RotationMatrix.rotate(fRotation);
//	m_fRotation = fRotation;
//	m_fSpeed = fSpeed;
//	m_Direction = RotationMatrix*(sf::Vector2f(0, -1));
//	mass = 5;
//	invMass = 1 / mass;
//}

LinearMovement::LinearMovement(float fRotation, float fSpeed, float fmass, sf::Vector2f fStartSpeed, bool bAccelerating)
{
	sf::Transform RotationMatrix = sf::Transform::Identity;
	RotationMatrix.rotate(fRotation);
	m_Direction = RotationMatrix*(sf::Vector2f(0, -1));
	m_fRotation = fRotation;
	m_fSpeed = fSpeed;
	m_fMaxSpeed = 20000;
	velocity = fStartSpeed;
	m_bAccelerating = bAccelerating;
	if (!m_bAccelerating) {
		velocity += (m_Direction*fSpeed);
	}
	mass = fmass;
	invMass = 1 / mass;
}

LinearMovement::~LinearMovement()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
}

void LinearMovement::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
}

void LinearMovement::OnFrameUpdate(sf::Time DeltaTime)
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	pPositionComponent->SetRotation(m_fRotation);

	//m_Movement = m_Direction * m_fSpeed * DeltaTime.asSeconds();
	if (m_bAccelerating) {
		sf::Vector2f accVec = m_Direction *m_fSpeed;

		auto length2 = [](const sf::Vector2f &vec) -> float { return vec.x * vec.x + vec.y * vec.y; };	//calculate vectorlenght squared

		float squaredSpeedLimit = m_fMaxSpeed * m_fMaxSpeed;
		if (length2(velocity + accVec * DeltaTime.asSeconds()) < squaredSpeedLimit)
			impulses.push_back(accVec);
	}
	sf::Vector2f forces;

	for (const auto& f : impulses)
		forces += f;
	impulses.clear();

	acceleration = forces * invMass;
	velocity += acceleration * DeltaTime.asSeconds();

	pPositionComponent->SetPosition(pPositionComponent->GetPosition()+ velocity* DeltaTime.asSeconds());
}

void LinearMovement::Serialize(SerializeNode *pParentNode)
{
    this->IMovement::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("Speed", ESerializeNodeType::Property, std::to_string(m_fSpeed)));
    pParentNode->AddElement(new SerializeNode("MaxSpeed", ESerializeNodeType::Property, std::to_string(m_fMaxSpeed)));
    pParentNode->AddElement(new SerializeNode("DirectionX", ESerializeNodeType::Property, std::to_string(m_Direction.x)));
    pParentNode->AddElement(new SerializeNode("DirectionY", ESerializeNodeType::Property, std::to_string(m_Direction.y)));
    pParentNode->AddElement(new SerializeNode("Rotation", ESerializeNodeType::Property, std::to_string(m_fRotation)));
    pParentNode->AddElement(new SerializeNode("Accelerating", ESerializeNodeType::Property, std::to_string(m_bAccelerating)));
}

IComponent* LinearMovement::Deserialize(SerializeNode* pNode)
{
    LinearMovement* pComponent = new LinearMovement(0.f, 0.f, 0.f, sf::Vector2f(), false);
    
    IMovement::Deserialize(pNode, pComponent);
    
    float x, y;
    
    pComponent->m_fSpeed = stof((pNode->GetNode("Speed"))->GetValue());
    pComponent->m_fMaxSpeed = stof((pNode->GetNode("MaxSpeed"))->GetValue());
    
    x = stof((pNode->GetNode("DirectionX"))->GetValue());
    y = stof((pNode->GetNode("DirectionY"))->GetValue());
    pComponent->m_Direction = sf::Vector2f(x, y);
    
    pComponent->m_fRotation = stof((pNode->GetNode("Rotation"))->GetValue());
    pComponent->m_bAccelerating = (stoi((pNode->GetNode("Accelerating"))->GetValue()) ? true : false);
    
    return pComponent;
}

