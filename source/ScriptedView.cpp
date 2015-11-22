#include <math.h>

#include "ScriptedView.h"

ScriptedView::ScriptedView(sf::FloatRect fViewSize, sf::Vector2f fMoveVector, float fSpeed)
{
    float fStep = (fSpeed / sqrt(pow(fMoveVector.x,2.0) + pow(fMoveVector.y,2.0)));
    
    m_MoveVector = fMoveVector;
    m_fSteps = fStep;
    m_fSpeed = fSpeed;
    
    m_pView = new sf::View(fViewSize);
}

ScriptedView::~ScriptedView()
{
    delete m_pView;
}

void ScriptedView::OnEventUpdate(sf::Time delta_time)
{
    float fStepsWithDeltaTime = m_fSteps * delta_time.asMilliseconds();
    m_pView->move(m_MoveVector * fStepsWithDeltaTime);
}

void ScriptedView::OnEventDraw(sf::RenderWindow* window)
{
    window->setView(*m_pView);
}