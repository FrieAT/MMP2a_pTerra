#include <math.h>

#include "Game.h"
#include "IPosition.h"
#include "ScriptedView.h"
#include "FrameManager.h"

ScriptedView::ScriptedView(sf::FloatRect fViewSize, sf::Vector2f fMoveVector, float fSpeed)
{
    float fStep = (fSpeed / sqrt(pow(fMoveVector.x,2.0) + pow(fMoveVector.y,2.0)));
    
    m_CurrentMovePosition = sf::Vector2f(0.f, 0.f);
    m_MoveVector = fMoveVector;
    m_fSteps = fStep;
    m_fSpeed = fSpeed;
    
    m_pView = new sf::View(fViewSize);
    
    FrameManager::RegisterEventObserver(this);
}

ScriptedView::~ScriptedView()
{
    FrameManager::UnregisterEventObserver(this);
    
    delete m_pView;
}

sf::FloatRect ScriptedView::GetViewport()
{
    return m_pView->getViewport();
}

void ScriptedView::OnFrameUpdate(sf::Time delta_time)
{
	if (m_CurrentMovePosition.x >= m_MoveVector.x && m_CurrentMovePosition.y >= m_MoveVector.y) {
		// TODO: Maybe repeating?
		return;
	}

	float fStepsWithDeltaTime = m_fSteps * delta_time.asSeconds();
	sf::Vector2f move = m_MoveVector * fStepsWithDeltaTime;
	m_CurrentMovePosition += move;
	m_pView->move(move);

	// Check if position from current game object is within Boundary
	IPosition* position_component = (IPosition*)GetAssignedGameObject()->GetComponent(EComponentType::Position);
	sf::Vector2f position = position_component->GetPosition();
	sf::Vector2f view_center = m_pView->getCenter();
	sf::Vector2f topleft_boundary(view_center.x - Game::m_iWindowWidth * 0.5f, view_center.y - Game::m_iWindowHeight * 0.5f);
	bool bPositionChanged = false;

	// Boundary correction in x-axis
	if (position.x < topleft_boundary.x) position.x = topleft_boundary.x;
	else if (position.x > topleft_boundary.x + Game::m_iWindowWidth) position.x = topleft_boundary.x + Game::m_iWindowWidth;

	// Boundary correction in y-axis
	if (position.y < topleft_boundary.y) position.y = topleft_boundary.y;
	else if (position.y > topleft_boundary.y + Game::m_iWindowHeight) position.y = topleft_boundary.y + Game::m_iWindowHeight;
	
	// Set new position
	position_component->SetPosition(position);
}

void ScriptedView::OnFrameDraw(sf::RenderWindow* window)
{
    window->setView(*m_pView);
}