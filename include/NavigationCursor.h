/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "INavigation.h"
#include "IFrameObserver.h"

class NavigationCursor : public INavigation, public IFrameObserver
{
public:
    NavigationCursor();
    ~NavigationCursor();
    void Init();
    void SetNavigationPoint(sf::Vector2f PointPosition);
    sf::Vector2f GetNavigationPoint();
    void SetNavigationActive(bool bActive, bool bForce = false);
	void SetNavigationCursorColor(sf::Color Color);
    void OnFrameDraw(sf::RenderWindow* pWindow);
    void OnFrameUpdate(sf::Time DeltaTime);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("NavigationCursor"); }
private:
    GameObject* m_pCursor;
};