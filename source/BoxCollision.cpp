#include "BoxCollision.h"
#include "CollisionManager.h"

#include <iostream>

BoxCollision::BoxCollision(float fWidth, float fHeight, IPosition* pos_)
	:pos(pos_)
	, m_fWidth(fWidth)
	, m_fHeight(fHeight)
	, hit(false)
{
	CollisionManager::GetInstance().RegisterCollisionbody(this);
	FrameManager::GetInstance().RegisterEventObserver(this);
}

BoxCollision::~BoxCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
	FrameManager::GetInstance().UnregisterEventObserver(this);

}

bool BoxCollision::colliding(ICollision* Collidingbody)
{
	BoxCollision* other = static_cast<BoxCollision*> (Collidingbody);
	sf::FloatRect a = sf::FloatRect(pos->GetPosition(),sf::Vector2f(m_fWidth,m_fHeight));
	sf::FloatRect b = sf::FloatRect();

	auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
	{
		return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
	};

	sf::Vector2f n = other->pos->GetPosition() - pos->GetPosition();		// Vector from A to B
	float a_extent = m_fWidth * 0.5f;			    // Calculate half extents along x axis
	float b_extent = other->m_fWidth * 0.5f;
	float x_overlap = a_extent + b_extent - abs(n.x);		// Calculate overlap on x axis
															// SAT test on x axis
	if (x_overlap > 0) {
		float a_extent = m_fHeight * 0.5f;		// Calculate half extents along y axis
		float b_extent = other->m_fHeight * 0.5f;
		float y_overlap = a_extent + b_extent - abs(n.y);	// Calculate overlap on y axis

		CollisionEvent col_ev;
		col_ev.Body1 = this->GetAssignedGameObject();
		col_ev.Body2 = other->GetAssignedGameObject();

		if (y_overlap > 0) {
			// Find out which axis is axis of least penetration
			if (x_overlap < y_overlap) {
				// Point towards B knowing that n points from A to B
				if (n.x < 0)
					col_ev.normal = sf::Vector2f(1.0f, 0.0f);
				else
					col_ev.normal = sf::Vector2f(-1.0f, 0.0f);
				CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);

				hit = true;
				return true;
			}
			else {
				// Point towards B knowing that n points from A to B
				if (n.y < 0)
					col_ev.normal = sf::Vector2f(0, 1);
				else
					col_ev.normal = sf::Vector2f(0, -1);
				CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);
				hit = true;
				return true;
			}
		}
	}
	hit = false;
	return false;
}

void BoxCollision::OnFrameDraw(sf::RenderWindow * pWindow)
{
	sf::RectangleShape test(sf::Vector2f(m_fWidth,m_fHeight));
	if (hit) test.setFillColor(sf::Color::Magenta);
	else test.setFillColor(sf::Color::Blue);
	test.setPosition(pos->GetPosition() - sf::Vector2f(m_fWidth/2, m_fHeight/2));

	pWindow->draw(test);

}
