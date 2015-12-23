#include "CircleCollision.h"
#include "CollisionManager.h"

#include <iostream>

CircleCollision::CircleCollision(float radius_,IPosition* pos_)
	:pos(pos_)
	,radius(radius_)
{
	CollisionManager::GetInstance().RegisterCollisionbody(this);
	FrameManager::GetInstance().RegisterEventObserver(this);
}

CircleCollision::~CircleCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
	FrameManager::GetInstance().UnregisterEventObserver(this);

}

bool CircleCollision::colliding(ICollision* Collidingbody)
{
	CircleCollision* other = static_cast<CircleCollision*> (Collidingbody);

	sf::Vector2f lenght_vec = other->pos->GetPosition() - pos->GetPosition();
	
	float lenght = lenght_vec.x*lenght_vec.x + lenght_vec.y*lenght_vec.y;
	float dis = radius + other->radius;
	dis = dis*dis;

	if (lenght < dis)
	{
		hit = true;
		CollisionEvent col_ev;
		col_ev.Body1 = this->GetAssignedGameObject();
		col_ev.Body2 = other->GetAssignedGameObject();
		col_ev.normal =  -(lenght_vec/4.f); 
		CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);
		return true;
	}
	else
	{
		hit = false;
		return false;
	}
}

void CircleCollision::OnFrameDraw(sf::RenderWindow * pWindow)
{
	sf::CircleShape test(radius);
	if(hit) test.setFillColor(sf::Color::Magenta);
	else test.setFillColor(sf::Color::Blue);
	test.setPosition(pos->GetPosition()- sf::Vector2f(radius, radius));
	
	// pWindow->draw(test);

}
