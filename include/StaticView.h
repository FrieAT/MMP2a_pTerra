/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "IView.h"

#include "IFrameObserver.h"

class StaticView : public IView, public IFrameObserver
{
public:
    StaticView(sf::FloatRect ViewSize);
    ~StaticView();
    void Init();
    void OnFrameUpdate(sf::Time DeltaTime);
    void OnFrameDraw(sf::RenderWindow* pWindow);
    void Serialize(SerializeNode* pParentNode);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("StaticView"); }
    
    sf::FloatRect GetViewport();
private:
    sf::View* m_pView;
};