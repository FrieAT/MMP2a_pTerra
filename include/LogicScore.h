/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "ILogic.h"
#include "ICollisionEventObserver.h"

class LogicScore : public ILogic, public ICollisionEventObserver
{
public:
	~LogicScore();
	void Init();
	void Action(GameObject* pPossibleOther = nullptr);
	void OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact);
	ELogicType GetLogicType() { return ELogicType::Score; }
	void Serialize(SerializeNode* pParentNode);
	static IComponent* Deserialize(SerializeNode* pNode);
	std::string GetComponentName() { return std::string("LogicScore"); }
private:

};