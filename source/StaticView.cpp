/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>

#include "Game.h"
#include "IPosition.h"
#include "IMovement.h"
#include "StaticView.h"
#include "FrameManager.h"

StaticView::StaticView(sf::FloatRect ViewSize)
{
    m_pView = new sf::View(ViewSize);
    
    FrameManager::GetInstance().RegisterEventObserver(this);
}

StaticView::~StaticView()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
    
    delete m_pView;
}

sf::FloatRect StaticView::GetViewport()
{
    return m_pView->getViewport();
}

void StaticView::OnFrameUpdate(sf::Time DeltaTime)
{
    
}

void StaticView::OnFrameDraw(sf::RenderWindow* pWindow)
{
    pWindow->setView(*m_pView);
}