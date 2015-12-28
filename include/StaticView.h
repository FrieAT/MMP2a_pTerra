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
    
    sf::FloatRect GetViewport();
private:
    sf::View* m_pView;
};