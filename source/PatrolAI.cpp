#include "PatrolAI.h"
#include "IPosition.h"
#include "ShipMovement.h"
#include "ObjectManager.h"

PatrolAI::PatrolAI()
{
}

PatrolAI::~PatrolAI()
{
	AIManager::GetInstance().UnregisterKIObserver(this);
}

void PatrolAI::Init()
{
	AIManager::GetInstance().RegisterKIObserver(this);
}

void PatrolAI::Update()
{
	IPosition* pPos = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	//pPos->SetPosition(pPos->GetPosition() + sf::Vector2f(0, 1));
	ShipMovement* pmov = static_cast<ShipMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));
	

	//if (m_target) {
	//	sf::Vector2f distance = m_FlyTo - pPos->GetCenter();
	//	
	//	auto length2 = [](const sf::Vector2f &vec) -> float { return vec.x * vec.x + vec.y * vec.y; };	//calculate vectorlenght squared


	//	float angle = atan2(distance.y , distance.x)* 180 / 3.14159265359;
	//	std::cout << angle << std::endl;

	//	//pmov->setShipState(0, true);
	//	//pmov->setShipState(2, false);

	//	//if (pPos->GetRotation() > fmod(angle - 5, 360) && pPos->GetRotation() < fmod(angle + 5, 360)) {
	//	//	pmov->setShipState(0, false);
	//	//	pmov->setShipState(2, true);

	//	//}
	//}

	if(m_Timer>0){
		pmov->setShipState(2, false);
		pmov->setShipState(3, false);
		pmov->setShipState(0, false);

	}
	else {
		pmov->setShipState(2, false);
		pmov->setShipState(3, true);
		pmov->setShipState(0, true);

		if (pPos->GetRotation() > fmod(m_FacingAngle-5,360) && pPos->GetRotation() < fmod(m_FacingAngle + 5, 360)) {
			m_FacingAngle = fmod(m_FacingAngle + 90, 360);
			m_Timer = 25;
		}
	}

	m_Timer--;
}

void PatrolAI::Serialize(SerializeNode * pParentNode)
{
}

IComponent * PatrolAI::Deserialize(SerializeNode * pNode)
{
	return nullptr;
}
