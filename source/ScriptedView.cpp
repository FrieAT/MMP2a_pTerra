#include <math.h>

#include "ScriptedView.h"

#include "ViewManager.h"

ScriptedView::ScriptedView(sf::FloatRect fViewSize, sf::Vector2f fMoveVector, float fSpeed)
{
    float fStep = (fSpeed / sqrt(pow(fMoveVector.x,2.0) + pow(fMoveVector.y,2.0)));
    
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = fMoveVector;
    m_fSteps = fStep;
    m_fSpeed = fSpeed;
    
    m_pView = new sf::View(fViewSize);
    
    ViewManager::RegisterEventObserver(this);
}

ScriptedView::~ScriptedView()
{
    ViewManager::UnregisterEventObserver(this);
    
    delete m_pView;
}

void ScriptedView::OnEventUpdate(sf::Time delta_time)
{
    if(m_CurrentMovePosition.x >= m_MoveVector.x && m_CurrentMovePosition.y >= m_MoveVector.y) {
        // TODO: Maybe repeating?
        return;
    }
    float fStepsWithDeltaTime = m_fSteps * delta_time.asMilliseconds();
    sf::Vector2f move = m_MoveVector * fStepsWithDeltaTime;
    m_CurrentMovePosition += move;
    m_pView->move(move);
}

void ScriptedView::OnEventDraw(sf::RenderWindow* window)
{
    window->setView(*m_pView);
}