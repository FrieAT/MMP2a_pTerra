/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "ILogic.h"
#include "IFrameObserver.h"

class LogicTime : public ILogic, public IFrameObserver
{
public:
	LogicTime(int iTimelimitSeconds);
	~LogicTime();
	void Init();
	int GetRemainingTime() { return static_cast<int>(m_fRemainingTime); }
	void Action(GameObject* pPossibleOther = nullptr);
	void OnFrameUpdate(sf::Time DeltaTime);
	ELogicType GetLogicType() { return ELogicType::Time; }
	void Serialize(SerializeNode* pParentNode);
	static IComponent* Deserialize(SerializeNode* pNode);
	std::string GetComponentName() { return std::string("LogicTime"); }
private:
	float m_fRemainingTime;
};