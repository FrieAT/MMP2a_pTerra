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
}

StaticView::~StaticView()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
    
    delete m_pView;
}

void StaticView::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
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

void StaticView::Serialize(SerializeNode *pParentNode)
{
    IView::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("ViewSizeX", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).left)));
    pParentNode->AddElement(new SerializeNode("ViewSizeY", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).top)));
    pParentNode->AddElement(new SerializeNode("ViewSizeWidth", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).width)));
    pParentNode->AddElement(new SerializeNode("ViewSizeHeight", ESerializeNodeType::Property, std::to_string((m_pView->getViewport()).height)));
}

IComponent* StaticView::Deserialize(SerializeNode *pNode)
{
    StaticView* pComponent = new StaticView(sf::FloatRect());
    
    IView::Deserialize(pNode, pComponent);
    
    sf::FloatRect ViewSize;
    ViewSize.left = stof((pNode->GetNode("ViewSizeX"))->GetValue());
    ViewSize.top = stof((pNode->GetNode("ViewSizeY"))->GetValue());
    ViewSize.width = stof((pNode->GetNode("ViewSizeWidth"))->GetValue());
    ViewSize.height = stof((pNode->GetNode("ViewSizeHeight"))->GetValue());
    pComponent->m_pView = new sf::View(ViewSize);
    
    return pComponent;
}